task :default => 'build:test:all'

namespace :build do
  task :release do
    system("g++ -fPIC -fno-common -c Source/*.cpp -I/usr/include")
    system("g++ -dynamiclib -W1 -o Build/libfloq.dylib *.o -ltokyocabinet -lpthread")
  end
  
  namespace :test do
    task :queue => :release do
      system('g++ -o Test/Build/queue-test Test/QueueTest.cpp -L./Build -I./Source -ltokyocabinet -lfloq')
    end
    
    task :sets => :release do
      system('g++ -o Test/Build/sets-test Test/SetsTest.cpp -L./Build -I./Source -ltokyocabinet -lfloq')
    end
    
    task :all => [:queue, :sets]
  end
end