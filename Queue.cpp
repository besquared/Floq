#include "Queue.h"

Queue::Queue(const string& path, const string& name) : BDB::BDB(path, name) {}

bool Queue::Push(const string& topic, const string& message) {
  return BDB::PutDup(topic, message);
}

bool Queue::Push(const vector<string>& topics, const string& message) {
  BDB::TransactionBegin();
  
  size_t count = topics.size();
  for(size_t i = 0; i < count; i++) {
    if(!BDB::PutDup(topics[i], message)) {
      BDB::TransactionAbort();
      return false;
    }
  }
  
  return BDB::TransactionCommit();
}

bool Queue::Get(const string& topic, string& message) {
  if(BDB::Get(topic, message)) {
    return BDB::Out(topic);
  } else {
    return false;
  }
}

void Queue::Get(const string& topic, vector<string>& messages, const int count) {
  string message;
  for(size_t i = 0; i < count; i++) {
    if(BDB::Get(topic, message)) {
      messages.push_back(message);
    }
  }
}

int Queue::Size(const string& topic) {
  return BDB::Count(topic);
}