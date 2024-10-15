#include <iostream>
#include <format>
#include <vector>
#include <cmath>
#include <stdint.h>

void printlog1(void)
{
 std::cout << "Custom log\n";
 std::vector<int32_t> values = {1, 10, 50, 100, 200, 500, 700, 900, 1000, 1100, 1200, 1500, 2000, 2500, 5000, 10000, 40000, 50000, 100000};
 for(auto& i : values)
    {
    double ii = i;
    double value = 5000;
    double baseline = 10;
    double soften = 2;

    double ratio = ii / value;
    double adjust = 0;
    double final = value;
    if (ratio < baseline)
    {
     adjust = 1.0 + ( (log(baseline) - log(ratio)) / soften );
     final = ii / (baseline * adjust);
    }

    std::cout << std::format("{:7}", i) << std::format("{:7.0f}", ii) << std::format("{:9.0f}", ratio);
    std::cout << std::format("{:6.2f}", log(baseline / ratio)) << std::format("{:6.2f}", log(baseline) - log(ratio));
    std::cout << std::format("{:6.2f}", log(baseline)) << std::format("{:6.2f}", adjust);
    std::cout << std::format("{:9.0f}", final);
    std::cout << "\n"; 
    }
 std::cout << "\n";
}

int main(int argc, const char* argv[])
{
 printlog1();
}
