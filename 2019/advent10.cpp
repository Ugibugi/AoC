#include <vector>
#include <string>
#include <fstream>
#include <map>
#include <set>
#include <iostream>
struct Point
{
    int x,y;
};
struct Asteroid
{
    Point pos;
    int score;
};
struct Ratio
{
    int a,b;
    bool operator==(const Ratio& oth) const
    {
        return oth.a*b == a*oth.b;
    }
    bool operator<(const Ratio& oth) const 
    {
        return a*oth.b < b*oth.a;
    }
};
Point diff(const Point& src,const Point& dst)
{
    return {dst.x - src.x, dst.y - src.y};
}
int main()
{
    std::vector<Asteroid> ast;
    {/*READ INPUT*/
        std::ifstream file("day10in");
        std::string line;
        int x=0,y=0;
        while(std::getline(file,line))
        {
            while(line.size() > 0)
            {
                char c = line.back();
                line.pop_back();
                if(c == '#')
                {
                    ast.push_back({{x,y},-1});
                }
                x++;
            }
            y++;
        }
    }
    std::vector<std::vector<double>> angles;
    Asteroid best{};
    //PART 1
    for(auto& a : ast)
    {
        std::set<Ratio> ratios;
        
        for(const auto& b : ast)
        {
            auto d = diff(a.pos,b.pos);
            Ratio r = {d.x,d.y};
            ratios.insert(r);
        }
        a.score = ratios.size();
        if(a.score > best.score)best = a;
    }
    std::cout << best.score << '\n';

    std::map<Ratio,std::vector<Point>> astrs;
    
    for(const auto& b : ast)
    {
        auto d = diff(best.pos,b.pos);
        Ratio r = {d.x,d.y};
        astrs[r].push_back(b.pos);
    }
    

}