// Day9_part1.cpp : 

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using std::ifstream;
using std::stringstream;
using std::string;
using std::vector;

int extrapolate(vector<int> &history);
bool checkZeros(vector<int> &nums);

int main()
{
    ifstream infile;
    infile.open("Input.txt");

    string line;
    vector<vector<int>> histories;
    while (getline(infile, line))
    {
        vector<int> readings;
        stringstream report(line);
        string data;
        while (report >> data)
        {
            readings.push_back(stoi(data));
        }
        histories.push_back(readings);
    }

    int sum = 0;
    for (int i = 0; i < histories.size(); ++i)
    {
        sum += extrapolate(histories.at(i));
    }

    std::cout << sum << std::endl;
}

int extrapolate(vector<int> &history)
{
    vector<vector<int>> differences;
    differences.push_back(history);
    int prev = 0;
    do
    {
        vector<int> difference;
        for (int i = 0; i < differences.at(prev).size() - 1; ++i)
        {
            difference.push_back(differences.at(prev).at(i + 1) - differences.at(prev).at(i));
        }
        differences.push_back(difference);
        ++prev;
    } while (!checkZeros(*differences.rbegin()));

    int difference;
    for (auto it = differences.rbegin() + 1; (it +1) != differences.rend(); ++it)
    {
        difference = *it->rbegin();
        (it + 1)->push_back(*(it + 1)->rbegin() + difference);
    }
    return *differences.at(0).rbegin();
}

bool checkZeros(vector<int>& nums)
{
    return std::all_of(nums.begin(), nums.end(), [](int i) {return i == 0; });
}
