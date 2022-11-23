#include <iostream>
#include <thread>
#include <tbb/tbb.h>
#include "Master.hh"

int Fib(int n)
{
  if(n<2)
    { return n; }
  else
  {
    int x, y;
    tbb::task_group g;
    g.run([&]{x=Fib(n-1);});
    g.run([&]{y=Fib(n-2);});
    g.wait();
    std::thread::id z = std::this_thread::get_id();
    std::cout << n << " ready, stdid " << z << std::endl;
    return x+y;
  }
}

int main()
{
 std::cout << "TBB version " << TBB_runtime_version() << std::endl;

 gazebo::Master master = gazebo::Master();
 master.Run();

 return 0;
}