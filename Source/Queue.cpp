#include "Queue.h"

Floq::Queue::Queue(const string& path, const string& name) : Floq::BDB::BDB(path, name) {}

bool Floq::Queue::Push(const string& topic, const string& message) {
  bool result = false;

  Floq::BDB::Lock();
  result = Floq::BDB::PutDup(topic, message);
  Floq::BDB::Unlock();
  
  return result;
}

bool Floq::Queue::Push(const string& topic, const vector<string>& messages) {
  bool result = false;
  bool failed = true;
  
  Floq::BDB::Lock();
  
  Floq::BDB::TransactionBegin();
  
  size_t count = messages.size();
  for(size_t i = 0; i < count; i++) {
    if(!Floq::BDB::PutDup(topic, messages[i])) {
      Floq::BDB::TransactionAbort();
      failed = true;
      result = false;
      break;
    }
  }
  
  if(!failed) result = Floq::BDB::TransactionCommit();
  
  Floq::BDB::Unlock();
  
  return result;
}

bool Floq::Queue::Push(const vector<string>& topics, const string& message) {
  bool result = false;
  bool failed = true;
  
  Floq::BDB::Lock();
  
  Floq::BDB::TransactionBegin();
  
  size_t count = topics.size();
  for(size_t i = 0; i < count; i++) {
    if(!Floq::BDB::PutDup(topics[i], message)) {
      Floq::BDB::TransactionAbort();
      failed = true;
      result = false;
      break;
    }
  }
  
  if(!failed) result = Floq::BDB::TransactionCommit();
  
  Floq::BDB::Unlock();
  
  return result;
}

bool Floq::Queue::Get(const string& topic, string& message) {
  bool result = false;
  
  Floq::BDB::Lock();
  if(Floq::BDB::Get(topic, message)) { 
    result = Floq::BDB::Out(topic);
  }
  Floq::BDB::Unlock();
}

// this needs to be transaction safe
void Floq::Queue::Get(const string& topic, vector<string>& messages, const int count) {
  string message;
  Floq::BDB::Lock();
  for(size_t i = 0; i < count; i++) {
    if(Floq::BDB::Get(topic, message)) {
      messages.push_back(message);
    }
  }
  Floq::BDB::Unlock();
}

int Floq::Queue::Size(const string& topic) {
  int result;
  Floq::BDB::Lock();
  result = Floq::BDB::Count(topic);
  Floq::BDB::Unlock();
  return result;
}