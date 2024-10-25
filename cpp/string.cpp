#include <iostream>
#include <string>
#include <format>

int main(int argc, const char* argv[])
{
 std::string one("one");
 std::string two = std::format("{}{}", "on", "e");
 std::string three = std::format("{}{}", "on", "ee");

 std::cout << (one == two) << " " << (one == three) << "\n";
}
