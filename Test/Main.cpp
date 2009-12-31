#include <Floq.h>
#include <boost/timer.hpp>

int main() {
  boost::timer t;
  
  Floq::Queue q("./Test", "myqueue");
  
  q.OpenWriter();
  
  t.restart();
  
  int message_count = 100000;
  
  vector<string> messages;
  for(int i = 0; i < message_count; i++) {
    messages.push_back("this is my message, lets see how fast it is now");
  }
  q.Push("insertions", messages);
  
  cout << "Queue size is now " <<  q.Size("insertions") << endl;
  cout << "Pushed " << message_count << " objects in " << t.elapsed() << " seconds" << endl;
  
  t.restart();
  
  string insertion;
  for(int i = 0; i < message_count; i++) {
    q.Get("insertions", insertion);
  }
  
  cout << "Queue size is now " <<  q.Size("insertions") << endl;
  cout << "Got objects in " << t.elapsed() << " seconds" << endl;
  
  q.Close();
  
  return 0;
}