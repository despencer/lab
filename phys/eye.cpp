#include <iostream>
#include <format>
#include <vector>
#include <cmath>
#include <stdint.h>

// in percents
int32_t opacity = 200;

void printsqrt(void)
{
 for(int32_t i=0; i<30; i++)
    {
    int32_t sq = std::sqrt(i);
    std::cout << i << "  " << sq << "\n";
    }
}

void printeye(void)
{
 std::vector<int32_t> energy = {0, 1, 2, 3, 4, 17, 18, 19, 31, 32, 33, 48, 49, 50, 51, 72, 97, 98 }; 

 for(auto& e:energy)
   {
   int32_t numcells = e * 100 / opacity;
   int32_t dim = std::sqrt(numcells);
   dim = (dim - 1) / 2;
   std::cout << "e " << e << " cells " << numcells << " dim " << dim << "\n";
   }
}

void printsensor(int32_t dim)
{
 for(int32_t x=-dim; x<=dim; x++)
   {
   for(int32_t y=-dim; y<=dim; y++)
       std::cout << x << "@" << y << "   ";
   std::cout << "\n";
   }
}

int main(int argc, const char* argv[])
{
// printeye();
 printsensor(0);
 std::cout << "\n";
 printsensor(1);
 std::cout << "\n";
 printsensor(2);
 std::cout << "\n";
 printsensor(3);
}
