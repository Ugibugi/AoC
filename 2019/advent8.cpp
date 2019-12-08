#include <fstream>
#include <array>
#include <algorithm>
#include <iostream>
#include <vector>
int main()
{
    constexpr uint width = 25;
    constexpr int height = 6;
    constexpr uint lsize = width*height;
    std::vector<std::array<uint,lsize>> layers;
    layers.reserve(100);
    { /*Read input file*/
        std::ifstream in("day8in");
        char digit;
        int i=0;
        layers.emplace_back();
        while(in >> digit)
        {
            uint num = digit - '0';
            if(i < lsize)
            {
                layers.back()[i] = num;
                i++;
            }
            else
            {
                i=0;
                layers.emplace_back()[i] = num;
                i++;
            }
        }
    }
    {/*PART 1*/
        int minZero = 100000;
        int n1,n2;
        for(const auto& layer : layers)
        {
            int n0 = std::count(layer.begin(),layer.end(),0);
            if(n0 < minZero)
            {
                minZero = n0;
                n1 = std::count(layer.begin(),layer.end(),1);
                n2 = std::count(layer.begin(),layer.end(),2);
            }
        }
        std::cout << n1*n2 << '\n';
    }
    {/*PART 2*/
        std::array<uint,lsize> image;
        for(int i=0; i<lsize; i++)
        {
            std::vector<uint> column(layers.size());
            std::generate(column.begin(),column.end(),[&,n=0]()mutable{ return layers[n++][i];});

            auto val = std::find_if(column.begin(),column.end(),[](uint a){ return a!=2;});
            image[i] = *val;
        }
        //RENDER
        for(int j=0;j<height;j++)
        {
            for(int i=0;i<width;i++)
            {
                uint pix = image[j*width + i];
                switch(pix)
                {
                    case 0: std::cout << '.'; break;
                    case 1: std::cout << '#'; break;
                    case 2: std::cout << ' '; break;
                    default: std::cout << 'E'; break;
                }
            }
            std::cout << '\n';
        }
    }
    

}