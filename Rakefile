task :default => :build

namespace :build do
  task :release do
    system("g++ -fPIC -fno-common -c BDB.cpp Queue.cpp")
    system("g++ -dynamiclib -W1 -o libfloq.dylib *.o -ltokyocabinet")
  end
  
  task :test do
    system('g++ -o floq-test Main.cpp -L. -ltokyocabinet -lfloq')
  end
end