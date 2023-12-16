// Day8_part2.cpp :


#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <utility>
#include <vector>
#include <numeric>


using std::string;
using std::ifstream;
using std::stringstream;
using std::map;
using std::pair;
using std::vector;
using std::lcm;


string::iterator circularNext(string& s, string::iterator& it);
vector<string> getStarts(map<string, pair<string, string>> nodes);
int getCycle(string instructions, string start, map<string, pair<string, string>> &nodes);

int main()
{
    ifstream infile;
    infile.open("Input.txt");
    string instructions;
    getline(infile, instructions);

    string location;
    map<string, pair<string, string>> nodes;
    while (getline(infile, location))
    {
        stringstream process(location);
        string name;
        pair<string, string> lr;

        process >> name;
        getline(process, location);
        location.erase(std::remove_if(location.begin(), location.end(),
            [](char c) -> bool
            {
                return !std::isalpha(c) && !std::isspace(c);
            }), location.end());
        process.str(location);
        process.clear();
        string left;
        string right;
        process >> left;
        process >> right;
        lr.first = left;
        lr.second = right;

        nodes[name] = lr;
    }

    vector<string> locations = getStarts(nodes);
    vector<int> cycles;
    for (int i = 0; i < locations.size(); ++i)
    {
        int cycleLength = getCycle(instructions, locations.at(i), nodes);
        cycles.push_back(cycleLength);
    }

    long long runningLCM;
    runningLCM = lcm(cycles.at(0), cycles.at(1));
    for (int i = 2; i < cycles.size(); ++i)
    {
        runningLCM = lcm(runningLCM, cycles.at(i));
    }
   
    std::cout << runningLCM << std::endl;;
}

string::iterator circularNext(string& s, string::iterator& it)
{
    it++;
    if (it == s.end())
    {
        it = s.begin();
    }
    return it;
}

vector<string> getStarts(map<string, pair<string, string>> nodes)
{
    vector<string> starts;
    for (auto it = nodes.begin(); it != nodes.end(); ++it)
    {
        if (*it->first.rbegin() ==  'A')
        {
            starts.push_back(it->first);
        }
    }
    return starts;
}

int getCycle(string instructions, string start, map<string, pair<string, string>> &nodes)
{
    map<string, int> endpoints;
    int steps = 0;
    bool cycle = false;
    string curNode = start;
    string::iterator it = instructions.begin();
    do
    {
        if (*it == 'L')
        {
            curNode = nodes[curNode].first;
            ++steps;
        }
        if (*it == 'R')
        {
            curNode = nodes[curNode].second;
            ++steps;
        }

        if (*curNode.rbegin() == 'Z')
        {
            if (endpoints.find(curNode) == endpoints.end())
            {
                endpoints[curNode] = steps;
            }
            else
            {
                return steps - endpoints[curNode];
            }
        }
        
        it = circularNext(instructions, it);

    } while (!cycle);

    return -1;
}