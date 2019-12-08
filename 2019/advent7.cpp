#include "intcode.hpp"
#include <algorithm>
int main()
{
    std::ifstream file("day7in");
    std::vector<int> prog;
    char buff[255];
    prog.reserve(1000);
    while (file.getline(buff, 255, ','))
    {
        prog.push_back(std::atoi(buff));
    }
    std::vector<Intcode> amps;
    std::vector<int> p{5,6,7,8,9};
    for(int i=0;i<5;i++)
    {
        amps.emplace_back(prog);
    }
    int max =0;
    do
    {
        //printf("running permutation { %d %d %d %d %d}\n",p[0],p[1],p[2],p[3],p[4]);
        int o=amps[4].run(amps[3].run(amps[2].run(amps[1].run(amps[0].run(0,p[0]),p[1]),p[2]),p[3]),p[4]);
        bool end =false;
        while(!amps[0].halted)
        {
            //printf("o = %d \n",o);
            o = amps[4].run(amps[3].run(amps[2].run(amps[1].run(amps[0].run(o)))));
            /*for(int i=0;i<5;i++)
            {
                if(amps[i].halted) printf("amp %d halted!\n",i);
            }*/
        }
        //printf("final o = %d \n",o);
        if(o>max)max = o;
        for(auto& a:amps)a.reset(prog);
    }while(std::next_permutation(std::begin(p), std::end(p)));
    std::cout << max << '\n';
}