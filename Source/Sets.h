#ifndef _floq_queue_h_
#define _floq_queue_h_

#include "BDB.h"
#include <pthread.h>

using namespace std;

namespace Floq {
  class Sets : public Floq::BDB {    
  public:
    Sets(const string& path, const string& name);
    
    bool Insert(const string& name, const string& value);
    bool Insert(const string& name, const vector<string>& values);
    bool Insert(const vector<string>& names, const string& value);

    bool Remove(const string& name, const string& value);
    bool Contains(const string& name, const string& value);
    
    bool Get(const string& name, vector<string>& results);
    bool Intersect(const vector<string>& names, vector<string>& results);
    bool Union(const vector<string>& names, vector<string>& results);
    bool Difference(const vector<string>& names, vector<string>& results);
    
    int Size(const string& name);
  };
}

#endif