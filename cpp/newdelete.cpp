#include <iostream>

void* operator new(size_t n)
{
 void* ret = malloc(n);
 std::cout << "Allocating " << n << " bytes at " << ret <<"\n";
 return ret;
}

void operator delete(void* p) throw()
{
 std::cout << "Freeing at " << p << "\n";
 free(p);
}

std::string loadstring(void)
{
 return "A very long string from a function";
}

class Test
{
  int a;
public:
  Test(int _a) { a = _a; std::cout << "Constructor Test" << a << "\n"; }
  virtual ~Test() { std::cout << "Destructor Test" << a << "\n"; }
};

int main(int argc, const char* argv[])
{
 std::cout << "start\n";
 delete (new Test(5));
 std::cout << "new-delete passed\n";
 {
  std::string b = "A very long string of many bytes";
 }
 std::cout << "simple string passed\n";
 {
  std::string c = loadstring();
  std::cout << "return from loadstring\n";
 }
 std::cout << "function string passed\n";
 {
  loadstring();
  std::cout << "return from loadstring without ret\n";
 }
 std::cout << "function string without ret passed\n";
 std::cout << "finish\n";
}