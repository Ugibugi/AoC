#include <array>
#include <iostream>
struct vec3
{
    int x,y,z;

    constexpr vec3 operator+(const vec3& v) const {
        return {x+v.x,y+v.y,z+v.z};
    }
    constexpr vec3 operator*(const int& a) const {
        return {x*a,y*a,z*a};
    }
    constexpr vec3 operator-(const vec3& v) const {
        return *this + (v*-1);
    }
    constexpr bool operator==(const vec3& v) const {
        return x == v.x && y == v.y && z == v.z;
    }
    constexpr int sum() const {
        return x+y+z;
    }
    constexpr int sumabs() const {
        return abs(x)+abs(y)+abs(z);
    }
};
std::ostream& operator<<(std::ostream& o, const vec3& v)
{
    return o <<'{'<<v.x<<','<<v.y<<','<<v.z<<'}';
}
struct Body
{
    vec3 pos;
    vec3 vel{};
    constexpr Body(vec3 p):pos(p){}
    constexpr bool operator==(const Body& v) const {
        return v.pos == pos;
    }
    constexpr void update(){pos = pos + vel;}
};
constexpr int twc(const int& a, const int& b)
{
    if(a>b)return 1;
    else if(a<b)return -1;
    else return 0;
}
constexpr vec3 twc(const vec3& a, const vec3& b)
{
    return {twc(a.x,b.x),twc(a.y,b.y),twc(a.z,b.z)};
}
constexpr vec3 grav(const Body& a,const Body& b)
{
    return twc(b.pos,a.pos);
}
typedef std::array<Body,4> State;
State f(const State& moons)
{
    State ret = moons;
    for(auto& a : ret)
    {  
        for(auto& b : ret)
        {
            if(a.pos == b.pos) continue; // self check

            a.vel = a.vel + grav(a,b);
        }
    }
    // std::cout <<'\n';
    for(auto& a : ret)
    {
        a.update();
    }
    return ret;
}
int main()
{
    constexpr std::array<Body,4> moons={
        Body({-14,-4,-11}),
        Body({-9,6,-7}),
        Body({4,1,4}),
        Body({2,-14,-9})
    };
    const auto first = moons;
    // std::array<Body,4> moons={
    //     Body({-1,0,2}),
    //     Body({2,-10,-7}),
    //     Body({4,-8,8}),
    //     Body({3,5,-1})
    // };
    auto calcEnergy = [&]()->int{
        int total =0;
        for(const auto& a : moons)
        {
            //std::cout << a.pos.sum() << '*' << a.vel.sum() << '\n';
            total += a.pos.sumabs() * a.vel.sumabs();
        }
        return total;
    };
    State t = f(moons);
    State h = f(t); // f(f(moons))
    uint64_t info=0;
    while(t!=h)
    {
        t=f(t);
        h=f(f(h));
        if(info++ % 100000000 == 0) std::cout << info <<'\n';
    }
    std::cout << "first loop done\n";
    t = moons;
    uint64_t i = 0;
    while(t!=h)
    {
        t = f(t);
        h = f(h);
        i++;
    }
    std::cout << i << '\n';
}