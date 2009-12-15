#ifndef _queue_included_
#define _queue_included_

#include "Common.h"

#include "BDB.h"

using namespace std;
using namespace Flow;

namespace Flow {
  class Queue : public BDB {
  public:
    Queue(const string& path, const string& name);
    
    bool Push(const string& topic, const string& message);
    bool Push(const vector<string>& topics, const string& message);
    
    bool Get(const string& topic, string& message);
    void Get(const string& topic, vector<string>& messages, const int count);
    
    int Size(const string& topic);
  };
}

#endif