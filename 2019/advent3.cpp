#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <sstream>
#include <vector>
#include <optional>
struct Ins
{
    char dir;
    int dist;
};
struct Point
{
    int x;
    int y;
};
struct Line
{
    Point start;
    Point end;
};
struct Line_entry
{
    Line line;
    int stepsToStart;
};
bool isPerp(const Line& a)
{
    if(a.start.x == a.end.x) return true;
    else return false;
}
std::optional<Point> intersect(const Line& a,const Line& b) 
{
    if(isPerp(a))
    {
        if(isPerp(b)) return std::optional<Point>();
        
        int lowy = a.start.y < a.end.y ? a.start.y : a.end.y;
        int highy = a.start.y < a.end.y ? a.end.y : a.start.y;
        
        int lx = b.start.x < b.end.x ? b.start.x : b.end.x;
        int rx = b.start.x < b.end.x ? b.end.x : b.start.x;

        if(b.start.y > lowy && b.start.y < highy && a.start.x > lx && a.start.x < rx)
        {
            return std::optional<Point>({a.start.x,b.start.y});
        }
        else return std::optional<Point>();
    }
    else
    {
       if(isPerp(b)) return intersect(b,a);
       else return std::optional<Point>();
    }
}
int dst(const Point& a,const Point& b)
{
    return abs(a.x-b.x)+abs(a.y-b.y);
}
int main()
{
    std::ifstream file("day3in");
    std::vector<Line_entry> lines;
    Point cursor;
    Point res = {10000000,10000000};
    int score = 10000000;
    int wire =0;
    for (std::string line; std::getline(file, line);)
    {
        cursor = {0,0};
        int steps=0;
        std::stringstream linestream(line);
        for(std::string entry; getline(linestream,entry,',');)
        {
            char dir = entry[0];
            int dist = std::atoi(entry.c_str()+1);
           
            Line l{cursor,cursor};
            switch(dir)
            {
                case 'R':l.end.x += dist;break;
                case 'L':l.end.x -= dist;break;
                case 'U':l.end.y += dist;break;
                case 'D':l.end.y -= dist;break;
                default: return -1; break; 
            }
            if(wire == 1)
            {
                for(auto pair : lines)
                {

                    if(auto ip = intersect(pair.line,l))
                    {
                        int score_ip = pair.stepsToStart + dst(*ip,pair.line.start) + steps + dst(*ip,l.start);
                        if(score_ip < score) score = score_ip;
                    }
                }
            }
            else
            {
                lines.push_back({l,steps});
            }
            cursor = l.end;
            steps += dist;
        }
        wire++;
    }
    
    std::cout << score << '\n';
    return 0;
}
