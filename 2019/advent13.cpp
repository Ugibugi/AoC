#include "intcode.hpp"
#include <array>
#include <unistd.h>
#include "ncurses.h"
constexpr int twc(const int& a, const int& b)
{
    if(a>b)return 1;
    else if(a<b)return -1;
    else return 0;
}
int main()
{
    auto win = initscr();
    curs_set(0);
    noecho();
    int frame =0;
    int ballx;
    int px;
    auto onInput = [&]()->int{
        char c = getch();
        if(c == 'a') return -1;
        else if(c == 'd')return 1;
        else{
            return twc(ballx,px);
        }
    };
    std::vector<int>outs;
    auto onOut = [&](uint64_t o){
        outs.push_back(o);
        if(outs.size() >= 3) 
        {
            int val = outs.back();outs.pop_back();
            int y = outs.back();outs.pop_back();
            int x = outs.back();outs.pop_back();

            if(x==-1) mvprintw(15,50,"Score: %d",val);
            else
            {
                char c=0;
                switch(val)
                {
                    case 0: c= ' ';break;
                    case 1: c= '@';break;
                    case 2: c= '#';break;
                    case 3: c= '_';px = x;break;
                    case 4: c= 'o';ballx = x;break;
                    default:break;
                }
                
                mvprintw(y,x,"%c",c);
                refresh();
            }
        }
        
    };
    Intcode game("day13in",onInput,onOut);
    game.run();
    nodelay(win,0);
    getch();
    endwin();
}