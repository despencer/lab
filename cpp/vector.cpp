#include <iostream>
#include <vector>

class Test
{
  int a;
public:
  Test(int _a) { a = _a; std::cout << "Constructor " << a << "\n"; }
  virtual ~Test() { std::cout << "Destructor " << a << "\n"; }
};

int main(int argc, const char* argv[])
{
 std::cout << "start\n";
 {
   std::vector<Test*> data;
   data.push_back(new Test(4));
   data.push_back(new Test(5));
   data.push_back(new Test(6));
   for(auto & t : data)
      delete t;
   data.clear();
 }
 std::cout << "finish\n";
}
