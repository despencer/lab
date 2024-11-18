#include <iostream>
#include <format>
#include <vector>
#include <cmath>
#include <stdint.h>

void drive(int32_t* energy, int32_t px, int32_t py, int32_t efficiency, int32_t* dx, int32_t* dy)
{
 if(px == 0 && py == 0) return;
// std::cout << "px=" << px << " py=" << py << " energy=" << *energy;
 int32_t total = (*energy) * 100 / efficiency;
// std::cout << " total=" << total;
 *dx = px * total / ( abs(px) + abs(py) );
 *dy = py * total / ( abs(px) + abs(py) );
// std::cout << "   dx=" << *dx << "   dy=" << *dy << " delta=" << (std::abs(*dx) + std::abs(*dy)) * efficiency / 100 << "\n";
 *energy -= (std::abs(*dx) + std::abs(*dy)) * efficiency / 100;
}

void printdrive(void)
{
 std::cout << "Driving\n";
 int32_t efficiency = 10000;

 std::vector<int32_t> px = {-10, 0, 10}, py = {-10, 0, 10};
 std::vector<int32_t> energy = {0, 10, 90, 100, 120, 150, 190, 200, 220 };

 std::cout << "        ";
 for(auto& i:px) for(auto& j:py) std::cout << std::format("{:14}", std::format("{:}@{:}", i, j));
 std::cout << "\n";

 for(auto& e:energy)
    {
    std::cout << std::format("{:6d}  ", e);
    for(auto& i:px) for(auto& j:py)
        {
        int32_t ee = e, dx=0, dy=0;
        drive(&ee, i, j, efficiency, &dx, &dy);
        std::cout << std::format("{:14}", std::format("{:}@{:}/{:}", dx, dy, ee));
        }
    std::cout << "\n";
    }
}

int main(int argc, const char* argv[])
{
 printdrive();
}
