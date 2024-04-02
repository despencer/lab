#include <iostream>
#include <format>

int main(int argc, const char* argv[])
{
 std::string str = std::format("The value is {}\n", 42);

 std::cout << str;
}
