task :default => 'build:test'

namespace :build do
  task :release do
    system("g++ -fPIC -fno-common -c Source/*.cpp -I/usr/include")
    system("g++ -dynamiclib -W1 -o Build/libfloq.dylib *.o -ltokyocabinet -lpthread")
  end
  
  task :test => :release do
    system('g++ -o floq-test Test/Main.cpp -L./Build -I./Source -ltokyocabinet -lfloq')
  end
end