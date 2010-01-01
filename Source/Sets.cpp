#include "Sets.h"

Floq::Sets::Sets(const string& path, const string& name) : Floq::BDB::BDB(path, name) {}

bool Floq::Sets::Insert(const string& name, const string& value) {
  bool result = false;
  
  BDBCUR* cursor = tcbdbcurnew(this->database);
  
  if(this->Size(name) == 0) {
    Floq::BDB::PutDup(name, value);
  } else if(!this->Search(name, value, cursor)) {
    cout << "Inserting " << value << " into list " << name << endl;
    tcbdbcurput(cursor, value.c_str(), value.size(), BDBCPAFTER);
  }
  
  tcbdbcurdel(cursor);
}

bool Floq::Sets::Search(const string& name, const string& value, BDBCUR* cursor) {
  int min = 0;
  int max =  this->Size(name);
  int mid = (int)((min + max) / 2);

  string midvalue;
  tcbdbcurjump(cursor, name.c_str(), name.size());
  for(int i = 0; i < mid; i++) { tcbdbcurnext(cursor); }
  
  while(min < max) {
    cout << "Going to position " << mid << endl;
  
    Floq::BDB::Get(cursor, midvalue);
    
    if(value == midvalue) {
      return true;
    } else if(value > midvalue) {
      cout << value << " is > " << midvalue << " min is going to " << mid + 1 << endl;
      min = mid + 1;
      for(int i = 0; i < mid; i++) { tcbdbcurnext(cursor); }
    } else { // value < midvalue
      cout << value << " is < " << midvalue << endl;
      max = mid - 1;
      for(int i = 0; i < mid; i++) { tcbdbcurprev(cursor); }
    }
    
    mid = (int)((min + max) / 2);
  }
  
  return false;
}

int Floq::Sets::Size(const string& name) {
  int result;
  Floq::BDB::Lock();
  result = Floq::BDB::Count(name);
  Floq::BDB::Unlock();
  return result;
}