#pragma once
#include <vector>
#include <fstream>
#include <string>
#include <iostream>
class Intcode
{
public:
    std::vector<int>mem;
    int ip=0;

    Intcode(std::string filename)
    {
        std::ifstream file("in");
        char buff[255];
        mem.reserve(1000);
        while (file.getline(buff, 255, ','))
        {
            mem.push_back(std::atoi(buff));
        }
        ip=0;
    }
    Intcode(const std::vector<int>& prog) : mem(prog.begin(),prog.end()), ip(0){}
    void reset(const std::vector<int>& prog)
    {
        mem = prog;
        ip=0;
    }
    
    int run(int retIndex=0)
    {
        while(true)
        {
            switch(mem[ip])
            {
            case 1:
                mem[mem[ip + 3]] = mem[mem[ip + 1]] + mem[mem[ip + 2]];
                ip+=4;
                break;
            case 2:
                mem[mem[ip + 3]] = mem[mem[ip + 1]] * mem[mem[ip + 2]];
                ip+=4;
                break;
            case 99:
                ip++;
                return mem[retIndex];
            default:
                std::cout << "error" << std::endl;
                return -1;
            }     
        }  
    }
};
