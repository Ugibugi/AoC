#include <iostream>
#include <map>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
class Tree
{
    
};
struct Node
{
        uint pid;
        std::vector<uint> children;
};
int countChildren(const std::map<uint,Node>& tree, uint id)
{
        int a = tree.at(id).children.size();
        for(const auto& child : tree.at(id).children)
        {
            a += countChildren(tree,child);
        }
        //printf("%d has %d children\n",id,a);
        return a;
}
int main()
{
    std::map<uint,Node> tree;
    std::ifstream file("day6in");
    char buff[255];
    while (file.getline(buff, 255, ')'))
    {
        uint parid=0;
        strncpy((char*)&parid,buff,3);
        //printf("%s = %d\n",buff,parid);
        uint childid=0;
        file.getline(buff,255,'\n');
        strncpy((char*)&childid,buff,3);
        tree[parid].children.push_back(childid);
        tree[childid].pid = parid;
    }
    /* PART 1
    int sum=0;
    for(const auto& it : tree)
    {
        sum+=countChildren(tree,it.first);
    }
    std::cout << sum << '\n';
    */
    uint myID = 0;
    uint santaID = 0;
    uint comID=0;
    strncpy((char*)&myID,"YOU",3);
    strncpy((char*)&santaID,"SAN",3);
    strncpy((char*)&comID,"COM",3);
    auto roadtoCOM = [&](uint start) -> std::vector<uint>{
        uint piter = start;
        std::vector<uint> road;
        while(piter != comID)
        {
            piter = tree[piter].pid;
            road.push_back(piter);
        }
        return road;
    };
    auto myRoad = roadtoCOM(myID);
    auto santaRoad= roadtoCOM(santaID);
    /* PART 2*/
    std::vector<uint> road;
    std::sort(myRoad.begin(),myRoad.end());
    std::sort(santaRoad.begin(),santaRoad.end());
    std::set_symmetric_difference(
        myRoad.begin(), myRoad.end(),
        santaRoad.begin(), santaRoad.end(),
        std::back_inserter(road));
    
    std::cout << road.size() << '\n';

    
    return 0;
}