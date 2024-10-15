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

int32_t propfunc2(int32_t value, double baseline, double soften)
{
 double dvalue = value;
 dvalue = (dvalue-baseline)/(baseline*soften);
 dvalue = soften * (1.0 - exp( -dvalue / soften) );
 return std::round(  (dvalue*baseline) + baseline );
}

void printexp0(void)
{
 std::vector<double> values = {-4, -3, -2, -1, -0.95, -0.9, -0.7, -0.5, -0.25, 0, 0.25, 0.5, 1, 2, 3, 4};
 for(auto& i : values)
    {
    double par = 1;
    double s1, s2;
/*    if(i < 0)
       {
       s1 = exp(-i/par);
       s2 = par * (1 - s1);
       }
    else
       {*/
       s1 = exp(-i/par);
       s2 = par * (1 - s1);
//       }
    double s3 = (i*1000)+1000;
    double s4 = (s2*1000)+1000;
    std::cout << std::format("{:8.1f}", i) << std::format("{:9.4f}", s1) << std::format("{:9.4f}", s2) << 
    std::format("{:9.2f}", s3) << std::format("{:9.2f}", s4) << std::format("{:8}", propfunc2( round(1000+i*1000), 1000, 1) ) << "\n";
    }
}

void printexp1(void)
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
    std::cout << std::format("{:7.2f}", s3) << std::format("{:6.2f}", s4) << std::format("{:6.2f}", s5)  << std::format("{:8.1f}", s6);
    std::cout << std::format("{:6}", s7) << " | " << std::format("{:6}", propfunc(i, baseline, soften) ) << std::format("{:7.3}", propfunc(i, baseline, soften)/ii );
    std::cout << std::format("{:8}", propfunc(i, baseline, 4.0)) << std::format("{:8}", propfunc(i, baseline, 0.75));
    std::cout << "\n"; 
    }
 std::cout << "\n";
}

void printexp2(void)
{
 std::cout << "Custom exponent\n";
 std::vector<int32_t> values = {5, 10, 50, 100, 200, 500, 700, 800, 900, 950, 1000, 1050, 1100, 1200, 1500, 2000, 2500, 5000};
 for(auto& i : values)
    {
    double ii = i;
    double baseline = 1000;
    double s2;
    if (ii < baseline)
        {
        s2 = baseline / ii;
        }
    else
        {
        s2 = ii / baseline;
        }
    double s3 = std::exp(1-s2);
    std::cout << std::format("{:5}", i) << std::format("{:5}", ii) << std::format("{:8.2f}", s2) << std::format("{:8.2f}", s3);
    std::cout << std::format("{:8.2f}", ii*s3);
    std::cout << "\n"; 
    }
}

int main(int argc, const char* argv[])
{
 printexp0();
}
