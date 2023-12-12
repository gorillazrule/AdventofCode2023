// Day8_part1.cpp : 


#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <utility>


using std::string;
using std::ifstream;
using std::stringstream;
using std::map;
using std::pair;


string::iterator circularNext(string& s, string::iterator& it);

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

    string node = "AAA";
    string target = "ZZZ";
    int steps = 0;
    string::iterator it = instructions.begin();
    do
    {
        if (*it == 'L')
        {
            node = nodes[node].first;
            ++steps;
        }
        else if (*it == 'R')
        {
            node = nodes[node].second;
            ++steps;
        }
        else
        {
            std::cout << "Something went wrong reading instructions." << std::endl;
        }
        it = circularNext(instructions, it);
        
    } while (node != target);
    std::cout << steps << std::endl;;
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
