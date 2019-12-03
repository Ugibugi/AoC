#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <sstream>
#include <vector>
#include "intcode.hpp"

int main()
{
    std::ifstream file("day2in");
    char buff[255];
    std::vector<int> mem;
    mem.reserve(1000);
    while (file.getline(buff, 255, ','))
    {
        mem.push_back(std::atoi(buff));
    }
    Intcode prog(mem);
    for(int a=0;a<100;a++)
    {
        for(int b=0;b<100;b++)
        {
            mem[1] = a;
            mem[2] = b;
            prog.reset(mem);
            if(prog.run() == 19690720)
            {
                std::cout << "a= " << a <<"\nb= " << b <<'\n';
            }
        }
    }
    return 0;
}
