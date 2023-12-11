// Day6_part2.cpp :
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

pair<int, int> getZeros(long long total, long long record);

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
    string partialTime = "";
    string partialRecord = "";
    while (timeStream >> t)
    {
        partialTime += t;
    }
    while (recordStream >> r)
    {
        partialRecord += r;
    }

    long long time = stoll(partialTime);
    long long record = stoll(partialRecord);

    pair<int, int> chargeTimes = getZeros(time, record);
    int wins = chargeTimes.second - chargeTimes.first + 1;

    std::cout << wins;
}

pair<int, int> getZeros(long long total, long long record)
{
    record++;
    long long square = total * total;
    long long sub = 4 * record;

    double root = sqrt(square - sub);

    int tcMax = floor((-1 * total - root) / -2);
    int tcMin = ceil((-1 * total + root) / -2);
    return std::make_pair(tcMin, tcMax);
}
