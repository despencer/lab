#include <iostream>
#include <vector>

class Test
{
  int a;
public:
  Test(int _a) { a = _a; std::cout << "Constructor " << a << "\n"; }
  virtual ~Test() { std::cout << "Destructor " << a << "\n"; }
};

void newdel(void)
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

class Vector
{
public:
 std::vector<int> v;
public:
 void print(const char* name)
   {
   std::cout << name << " [ ";
   for(auto& i : v) std::cout << i << " ";
   std::cout << "]\n";
   }
};

void copy(void)
{
 Vector v1, v2; v1.v = {1, 2, 3, 4}; v1.print("v1");
 v2.v = {5, 6, 7}; v2.print("v2");
 v2.v = v1.v;
 v2.print("v2");
 v1.v[0] = 11;
 v1.print("v1");
 v2.print("v2");
}

int main(int argc, const char* argv[])
{
 copy();
}
