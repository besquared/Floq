#include <Sets.h>
#include <boost/timer.hpp>

int main() {
  boost::timer t;
  
  Floq::Sets sets("./Test", "mysets");
  
  sets.Truncate();
  sets.OpenWriter();
  
  for(int i = 0; i < 2; i++) {
    sets.Insert("mylist", "myvalue");
  }
  
  sets.Insert("mylist", "myvalue4");
  sets.Insert("mylist", "myvalue3");
  sets.Insert("mylist", "myvalue5");
  
  cout << "Set size is now " << sets.Size("mylist") << endl;
  
  vector<string> values;
  sets.Get("mylist", values);
  
  vector<string>::iterator value;
  for(value = values.begin(); value != values.end(); value++) {
    cout << *value << ", ";
  }
  cout << endl;
  
  t.restart();
  
  // int message_count = 10;
  // 
  // vector<string> messages;
  // for(int i = 0; i < message_count; i++) {
  //   messages.push_back("this is my message, lets see how fast it is now");
  // }
  
  // t.restart();
  // 
  // string insertion;
  // for(int i = 0; i < message_count + 1; i++) {
  //   // sets.Get("insertions", insertion);
  // }
  
  sets.Close();
  
  return 0;
}