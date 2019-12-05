#include <array>
#include <cmath>
#include <iostream>
#include <map>
typedef std::array<char,6> NumArr;

NumArr from(int in)
{
    NumArr ret; 
    for(int i=0;i<ret.size();i++)
    {
        int val = (in/int(pow(10,i)))%10;
        ret[i] = val;  
    }
    return ret;
}
void printArr(const NumArr& num)
{
    std::cout << "{ ";
    for(int i=0;i<num.size();i++)
    {
        std::cout << int(num[i]) <<", ";

    }
    std::cout << "}\n";
}
bool isAsc(const NumArr& num)
{
    
    for(int i=1;i<num.size();i++)
    {
        if(num[i-1] < num[i])return false;
        
    }

    return true;// && true;
}
bool hasPair(const NumArr& num)
{
    bool hasPair=false;
    for(int i=1;i<num.size();i++)
    {
        if(num[i-1] == num[i])hasPair = true;
    }
    return hasPair;
}
bool uniquePair(const NumArr& num)
{
    std::map<char,int> numPairs;
    for(int i=1;i<num.size();i++)
    {
        if(num[i-1] == num[i])numPairs[num[i]]++;
    }
    
    for(const auto& it : numPairs)
    {
        if(it.second == 1)return true;
    }
    return false;
}
int main()
{
    int start = 108457;
    int end = 562041;
    int count =0;
    std::cout << std::boolalpha << isAsc(from(123456));
    for(int i=start;i<end;i++)
    {
        auto ar = from(i);
        //printArr(ar);
        if(isAsc(ar) && uniquePair(ar))count++;
       // else printf("rejected: %d\n",i);
    }
    std::cout << count << '\n';
}