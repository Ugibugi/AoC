#include <set>
#include "intcode.hpp"
struct Point
{
    int x,y;
    bool operator<(const Point& o) const{
        return 1024*x+y < 1024*o.x+o.y;
    }
};
class Robot
{
    public:
        std::array<std::array<int,500>,500> space{};
        Intcode prog;
        Robot():prog("day11in"){
            pos={250,250};
            dir=0;
        }
        Point pos;
        int dir;
        std::set<Point> painted;
    void run()
    {
        space[pos.x][pos.y] = 1;
        while(true)
        {

            int color = space[pos.x][pos.y];
            int newColor = prog.run(color);
            if(prog.halted)break;
            int ndir = prog.run();

            painted.insert(pos);
            space[pos.x][pos.y]=newColor;

            if(ndir == 1)
            {
                dir++;
                dir = dir>3?0:dir;
            }
            else
            {
                dir--;
                dir = dir<0?3:dir;
            }
            switch(dir)
            {
                case 0: pos.y++;break;
                case 1: pos.x++;break;
                case 2: pos.y--;break;
                case 3: pos.x--;break;
                default:printf("dupa");break;
            }
        }
        //part 1
        //std::cout << painted.size() << '\n';
    }

};

int main()
{
    Robot r;
    r.run();
    for(const auto& arr : r.space)
    {
        for(const auto& p : arr)
        {
            switch (p)
            {
            case 1:
                std::cout << '#';
                break;
            case 0:
                std::cout << '.';
            
            default:
                break;
            }
        }
        std::cout << '\n';
    }
    return 0;
}