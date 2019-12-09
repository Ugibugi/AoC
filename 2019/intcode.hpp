#pragma once
#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <array>
#include <cmath>
#include <sstream>
#include <unordered_map>

typedef std::array<int64_t,5> Ins;
typedef std::unordered_map<int64_t,int64_t> Prog;

class Intcode
{
public:
    Prog mem;
    std::vector<int64_t> in;
    int64_t out;
    bool halted = false;
    int64_t ip=0;
    int64_t relBase=0;
    struct
    {
        int64_t opcode;
        std::array<int64_t,3> accessMode; 
    }instr;
    
    Intcode(std::string filename)
    {
        std::ifstream file(filename);
        char buff[255];
        int64_t i=0;
        while (file.getline(buff, 255, ','))
        {
            mem[i]=std::atoll(buff);
            //std::cout << buff << " = " << mem[i] << '\n';
            i++;
        }
        ip=0;
    }
    Intcode(const Prog& prog) : mem(prog), ip(0){}
    void reset(const Prog& prog)
    {
        mem = prog;
        ip=0;
        halted = false;
        relBase =0;
    }

    int64_t& at(int64_t addr,int64_t access)
    {
        if(access == 1) return mem[addr];
        else if(access == 2)return mem[mem[addr]+relBase];
        else return mem[mem[addr]];
    }
    int64_t& arg(int64_t n)
    {
        return at(ip+n,instr.accessMode[n-1]);
    }
    void parseInstr()
    {
        Ins ret; 
        int64_t instruction = mem[ip];
        for(int64_t i=0;i<ret.size();i++)
        {
            int64_t val = (instruction/int64_t(pow(10,i)))%10;
            ret[i] = val;  
        }
        instr.opcode = instruction%100;
        for(int64_t i=2;i<ret.size();i++)
        {
            instr.accessMode[i-2] = ret[i];
        }
    }
    int64_t input(std::istream& def = std::cin)
    {
        int64_t a;
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
    uint64_t run(Types ...args)
    {
        if(halted) 
        {
            printf("HALT RETURN\n");
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
                //printf("HALT %d\n",out);
                return out;
                break;
            case 3: // IN
                arg(1) = input();
                ip+=2;
                break;
            case 4: //OUT
                out = arg(1);
                ip+=2;
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
            case 9: //ADDBASE 
                relBase += arg(1);
                ip+=2;
                break;
            default:
                printf("Bad instruction \n ip=%d  mem[ip]=%d \n opcode = %d access={ %d, %d, %d } \n args = %d %d %d \n",
                                           ip,    mem[ip],instr.opcode, instr.accessMode[0], instr.accessMode[1], instr.accessMode[2],arg(1),arg(2),arg(3));
                return -1;
            } 
               
        }  
    }
    template<typename... Types>
    void runAll(Types ...args)
    {
        (in.push_back(std::forward<Types>(args)), ...);
        while(!halted)
        {
            std::cout << "Output: "  << run() << '\n';
        }
    }
};
