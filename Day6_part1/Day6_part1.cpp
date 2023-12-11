// Day6_part1.cpp :

#include <iostream>
#include <utility>
#include <cmath>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cassert>



using std::pair;
using std::ifstream;
using std::stringstream;
using std::string;
using std::vector;

pair<int, int> getZeros(int total, int record);

int main()
{
    ifstream infile;
    infile.open("Input.txt");
    
    string t;
    string r;
    
    getline(infile, t);
    getline(infile, r);
    infile.close();

    stringstream timeStream(t);
    stringstream recordStream(r);

    vector<int> times;
    vector<int> records;
    while (timeStream >> t)
    {
        times.push_back(stoi(t));
    }
    while (recordStream >> r)
    {
        records.push_back(stoi(r));
    }

    assert(times.size() == records.size());

    int winWays = 1;
    pair<int, int> chargeTimes;

    for (int i = 0; i < times.size(); ++i)
    {
        chargeTimes = getZeros(times.at(i), records.at(i));
        int ways = chargeTimes.second - chargeTimes.first + 1;
        winWays *= ways;
    }

    
    std::cout << winWays;
}

pair<int, int> getZeros(int total, int record)
{
    record++;
    int tcMax = floor((-1 * total - sqrt(pow(total, 2) - 4 * record)) / -2);
    int tcMin = ceil((-1 * total + sqrt(pow(total, 2) - 4 * record)) / -2);
    return std::make_pair(tcMin, tcMax);
}
