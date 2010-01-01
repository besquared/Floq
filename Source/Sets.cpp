#include "Sets.h"

Floq::Sets::Sets(const string& path, const string& name) : Floq::BDB::BDB(path, name) {}

bool Floq::Sets::Insert(const string& name, const string& value) {
  bool result = false;
  string key = name + "/" + value;
  
  if(this->size(key) == 0) {
    Floq::BDB::Put(key, "");
  }
}

bool Floq::Sets::Contains(const string& name, const string& value) {
  tcbdbvnum(TCBDB *bdb, const void *kbuf, int ksiz)
}

bool Get(const string& name, vector<string>& results) {
  // use FWMKEYS
}

// use FWMKEYS instead
int Floq::Sets::Size(const string& name) {
  int result;
  Floq::BDB::Lock();
  result = Floq::BDB::Count(name);
  Floq::BDB::Unlock();
  return result;
}