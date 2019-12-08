#pragma once
#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <array>
#include <cmath>
#include <sstream>

typedef std::array<int,5> Ins;


class Intcode
{
public:
    std::vector<int>mem;
    std::vector<int> in;
    int out;
    bool halted = false;
    int ip=0;
    struct
    {
        int opcode;
        std::array<int,3> accessMode; 
    }instr;
    
    Intcode(std::string filename)
    {
        std::ifstream file(filename);
        char buff[255];
        mem.reserve(1000);
        while (file.getline(buff, 255, ','))
        {
            mem.push_back(std::atoi(buff));
        }
        ip=0;
    }
    Intcode(const std::vector<int>& prog) : mem(prog), ip(0){}
    void reset(const std::vector<int>& prog)
    {
        mem = prog;
        ip=0;
        halted = false;
    }

    int& at(int addr,int immediate=0)
    {
        if(immediate) return mem[addr];
        else return mem[mem[addr]];
    }
    int& arg(int n)
    {
        return at(ip+n,instr.accessMode[n-1]);
    }
    void parseInstr()
    {
        Ins ret; 
        int instruction = mem[ip];
        for(int i=0;i<ret.size();i++)
        {
            int val = (instruction/int(pow(10,i)))%10;
            ret[i] = val;  
        }
        instr.opcode = instruction%100;
        for(int i=2;i<ret.size();i++)
        {
            instr.accessMode[i-2] = ret[i];
        }
    }
    int input(std::istream& def = std::cin)
    {
        int a;
        if(in.empty()) def >> a;
        else
        {
            a = in.back();
            in.pop_back();
        }
        //printf("Put in: %d \n",a);
        return a;
        
    }
    template<typename... Types>
    int run(Types ...args)
    {
        if(halted) 
        {
            //printf("HALT RETURN\n");
            return out;
        }
        //printf("Running prog\n");
        (in.push_back(std::forward<Types>(args)), ...);
        while(true)
        {
            parseInstr(); 
            switch(instr.opcode)
            {
            case 1: //ADD
                arg(3) = arg(1) + arg(2);
                ip+=4;
                break;
            case 2: // MUL
                arg(3) = arg(1) * arg(2);
                ip+=4;
                break;
            case 99: // HALT
                ip++;
                halted = true;
                //printf("returning %d\n",out);
                return out;
            case 3: // IN
                arg(1) = input();
                ip+=2;
                break;
            case 4: //OUT
                out = arg(1);
                ip+=2;
                //printf("output: %d\n",out);
                return out;
                break;
            case 5: //J IF TRUE
                if(arg(1)) ip = arg(2);
                else ip+=3;
                break;
            case 6: //J IF FALSE
                if(arg(1) == 0) ip = arg(2);
                else ip+=3;
                break;
            case 7: //LT
                if(arg(1) < arg(2)) arg(3) = 1;
                else arg(3) = 0;
                ip+=4;
                break;
            case 8: //EQ 
                if(arg(1) == arg(2)) arg(3) = 1;
                else arg(3) = 0;
                ip+=4;
                break;
            default:
                printf("Bad instruction \n ip=%d  mem[ip]=%d \n opcode = %d access={ %d, %d, %d } \n args = %d %d %d \n",
                                           ip,    mem[ip],instr.opcode, instr.accessMode[0], instr.accessMode[1], instr.accessMode[2],arg(1),arg(2),arg(3));
                return -1;
            } 
               
        }  
    }
};
