#include "Queue.h"

Floq::Queue::Queue(const string& path, const string& name) : 
Floq::BDB::BDB(path, name) {
  if(pthread_mutex_init(&this->mutex, NULL) != 0) {
    throw "Could not initialize queue mutex.";
  }
}

Floq::Queue::~Queue() {
  pthread_mutex_destroy(&this->mutex);
}

void Floq::Queue::Lock() {
  pthread_mutex_lock(&this->mutex);
}

void Floq::Queue::Unlock() {
  pthread_mutex_unlock(&this->mutex);
}

bool Floq::Queue::Push(const string& topic, const string& message) {
  bool result = false;

  this->Lock();
  result = Floq::BDB::PutDup(topic, message);
  this->Unlock();
  
  return result;
}

bool Floq::Queue::Push(const string& topic, const vector<string>& messages) {
  bool result = false;
  bool failed = true;
  
  this->Lock();
  
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
  
  this->Unlock();
  
  return result;
}

bool Floq::Queue::Push(const vector<string>& topics, const string& message) {
  bool result = false;
  bool failed = true;
  
  this->Lock();
  
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
  
  this->Unlock();
  
  return result;
}

bool Floq::Queue::Get(const string& topic, string& message) {
  bool result = false;
  
  this->Lock();
  if(Floq::BDB::Get(topic, message)) { 
    result = Floq::BDB::Out(topic);
  }
  this->Unlock();
}

void Floq::Queue::Get(const string& topic, vector<string>& messages, const int count) {
  string message;
  this->Lock();
  for(size_t i = 0; i < count; i++) {
    if(Floq::BDB::Get(topic, message)) {
      messages.push_back(message);
    }
  }
  this->Unlock();
}

int Floq::Queue::Size(const string& topic) {
  int result;
  this->Lock();
  result = Floq::BDB::Count(topic);
  this->Unlock();
  return result;
}