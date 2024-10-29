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

// calculates degradation curve for not beeing at optimum
// dvalue: requested value
// baseline: optimum point
// soften: a soften parameter
double curve(double dvalue, double baseline, double soften)
{
 dvalue = (dvalue-baseline)/(baseline*soften);
 dvalue = soften * (1.0 - exp( -dvalue / soften) );
 return (dvalue*baseline) + baseline;
}

// calculates adjustments for performance degradation for exceeding capacity
// part: requested value
// value: a value that present
// capacity: a maximum capacity ratio 
// soften: a soften parameter
double ratio(double part, double value, double capacity, double soften)
{
 double ratio = value / part;
 if (ratio < capacity)
    {
    double adjust = 1.0 + ( (log(capacity) - log(ratio)) / soften );
    return value / (capacity * adjust);
    }
 return part;
}

int32_t propfunc2(int32_t value, double baseline, double soften)
{
 double dvalue = value;
 dvalue = (dvalue-baseline)/(baseline*soften);
 dvalue = soften * (1.0 - exp( -dvalue / soften) );
 int32_t ret = std::round(  (dvalue*baseline) + baseline );
 if(ret > 0) return ret;
 return 0;
}

void next1(int32_t* temperature, int32_t emission, int32_t dissipation)
{
 *temperature = ( (*temperature) / dissipation ) + emission;
}

void next2(int32_t* temperature, int32_t emission, int32_t dissipation)
{
 *temperature = ( (*temperature) - ((*temperature) / dissipation) ) + emission;
}

// temperatute: how many energy cell contains. This energy is going to be harvested
// energy: how many energy module already contains. This energy is a recipient for harvesting and a source for appetite
// appetite: how many energy a mdoule invests into the harvesting
// efficiency: how many energy is harvested in the best case per one appetite unit
// capacity: how many modules can harvest simoultaneously without performance degradation
void harvest1(int32_t* temperature, int32_t* energy, int32_t appetite, int32_t efficiency, int32_t capacity)
{
 if( appetite > *energy)
    appetite = *energy;
 int32_t delta = std::round( ratio( curve(appetite, 10, 1.235) * efficiency, *temperature, capacity, 3));
 if (delta < 0) delta = 0;
 *energy += delta - appetite;
 *temperature -= delta;
}

void harvest2(int32_t* temperature, int32_t* energy, int32_t appetite, int32_t efficiency, int32_t capacity)
{
 if( appetite > *energy)
    appetite = *energy;
 int32_t delta = appetite * efficiency;
 if(delta > 0)
   delta /= 1+(900/delta);
 delta -= 5 * (delta/1100);
 if( *temperature > 0)
    delta /= 1+(capacity/(*temperature));
 if( *temperature < delta)
    delta = 0;
 *energy += delta - appetite;
 *temperature -= delta;
}

void printsun(void)
{
 int32_t temperature = 0;
 for(int i=0; i<130; i++)
    {
    std::cout << std::format("{:8}", temperature) << "\n";
    next2(&temperature, 10000, 10);
    }
}

void printharvest(void)
{
 std::vector<int32_t> appetite = { 0, 1, 2, 3, 4, 5, 7, 10, 12, 15, 20, 25, 30, 40, 50 };
 std::vector<int32_t> temperature = { -10000, -10, 0, 200, 500, 1000, 2000, 4000, 6000, 8000, 10000, 15000, 20000, 30000, 50000, 100000 };

 std::cout << "        ";
 for(auto& t : temperature)
    std::cout << std::format("{:9}", t);
 std::cout << "\n";

 for(auto& a : appetite)
   {
   std::cout << std::format("App {:2} |", a);
   for(auto& t: temperature)
      {
      int32_t temp = t;
      int32_t energy = 35;
      harvest1(&temp, &energy, a, 100, 10);
      std::cout << std::format("{:9}", energy);
      }
   std::cout << "\n        ";
   for(auto& t: temperature)
      {
      int32_t temp = t;
      int32_t energy = 35;
      harvest1(&temp, &energy, a, 100, 10);
      std::cout << std::format("{:9}", temp);
      }
   std::cout << "\n";
   }
}

void printharvest2(void)
{
 std::vector<int32_t> appetite = { 0, 1, 2, 3, 4, 5, 7, 10, 12, 15, 20, 25, 30, 40, 50 };
 std::vector<int32_t> temperature = { -10000, -10, 0, 200, 500, 1000, 2000, 4000, 6000, 8000, 10000, 15000, 20000, 30000, 50000, 100000 };

 std::cout << "        ";
 for(auto& t : temperature)
    std::cout << std::format("{:9}", t);
 std::cout << "\n";

 for(auto& a : appetite)
   {
   std::cout << std::format("App {:2} |", a);
   for(auto& t: temperature)
      {
      int32_t temp = t;
      int32_t energy = 40;
      harvest2(&temp, &energy, a, 100, 900);
      std::cout << std::format("{:9}", energy-40+a);
      }
   std::cout << "\n        ";
/*   for(auto& t: temperature)
      {
      int32_t temp = t;
      int32_t energy = 35;
      harvest2(&temp, &energy, a, 100, 10);
      std::cout << std::format("{:9}", temp);
      }*/
   std::cout << "\n";
   }
}

int main(int argc, const char* argv[])
{
 printharvest2();
}