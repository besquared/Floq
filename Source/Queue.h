#ifndef _floq_queue_h_
#define _floq_queue_h_

#include "BDB.h"
#include <pthread.h>

using namespace std;

namespace Floq {
  class Queue : public Floq::BDB {
  protected:
    pthread_mutex_t mutex;
    
  public:
    Queue(const string& path, const string& name);
    ~Queue();
    
    void Lock();
    void Unlock();
    
    bool Push(const string& topic, const string& message);
    bool Push(const string& topic, const vector<string>& messages);
    bool Push(const vector<string>& topics, const string& message);
    
    bool Get(const string& topic, string& message);
    void Get(const string& topic, vector<string>& messages, const int count);
    
    int Size(const string& topic);
  };
}

#endif