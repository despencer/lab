#include <iostream>
#include <format>
#include <vector>
#include <cmath>
#include <stdint.h>

int32_t propfunc(int32_t value, double baseline, double soften)
{
 double dvalue = value;
 dvalue = (dvalue-baseline)/(baseline*soften);
 if(dvalue < 0)
    dvalue = 1.0 - std::exp(-dvalue);
 else
    dvalue = std::exp(dvalue) - 1.0;
 return std::round(  (dvalue*baseline) + baseline );
}

void printexp(void)
{
 std::cout << "Custom exponent\n";
 std::vector<int32_t> values = {0, 10, 50, 100, 200, 500, 700, 900, 1000, 1100, 1200, 1500, 2000, 2500, 5000};
 for(auto& i : values)
    {
    double ii = i;
    double baseline = 1000;
    double soften = 2;

    double s2 = (ii-baseline)/(baseline*soften);
    double s3, s4, s5, s6;
    int32_t s7;
    if(s2 < 0)
      {
      s3 = -s2;
      s4 = std::exp(s3);
      s5 = 1.0 - s4;
      s6 = (s5 * baseline) + baseline;
      s7 = std::round(s6);
      }
    else
      {
      s3 = s2;
      s4 = std::exp(s3);
      s5 = s4 - 1.0;
      s6 = (s5 * baseline) + baseline;
      s7 = std::round(s6);
      }

    std::cout << std::format("{:5}", i) << std::format("{:5}", ii) << std::format("{:7}", ii-baseline) << std::format("{:7.2f}", s2);
    std::cout << std::format("{:7.2f}", s3) << std::format("{:6.2f}", s4) << std::format("{:6.2f}", s5) << std::format("{:8.1f}", s6);
    std::cout << std::format("{:6}", s7) << " | " << std::format("{:6}", propfunc(i, baseline, soften) );
    std::cout << std::format("{:8}", propfunc(i, baseline, 4.0)) << std::format("{:8}", propfunc(i, baseline, 0.75));
    std::cout << "\n"; 
    }
 std::cout << "\n";
}

int main(int argc, const char* argv[])
{
 printexp();
}
