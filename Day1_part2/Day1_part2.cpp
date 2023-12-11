// Day1.cpp :


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctype.h>
#include <map>

void populateDigits(std::map<std::string, int>& dig);

using std::ifstream;
using std::string;
using std::vector;


int main()
{
    ifstream infile;
    infile.open("Input.txt");

    string line;
    string num;
    vector<int> nums;
    int sum = 0;
    size_t ifirst;
    size_t ilast;


    std::map<string, int> digits;
    populateDigits(digits);
    std::map<size_t, int> asciipos;
    std::map<size_t, int, std::greater<size_t>> asciirpos;

    while (std::getline(infile, line))
    {
        string::iterator first = line.begin();
        string::reverse_iterator last = line.rbegin();
        num = "";

        //Loop through and find the position of the first and last actual digit
        while (!isdigit(*first))
        {
            first++;
        }
        ifirst = std::distance(line.begin(), first);
        while (!isdigit(*last))
        {
            last++;
        }
        ilast = line.size() - 1 - std::distance(line.rbegin(), last);

        //Loop through and find the position of the first and last ascii digit
        for (auto i = digits.begin(); i != digits.end(); ++i)
        {
            size_t pos = line.find(i->first);
            if (pos != string::npos)
            {
                asciipos.emplace(pos, i->second);
                size_t rpos = line.rfind(i->first);
                if (rpos != string::npos)
                {
                    asciirpos.emplace(rpos, i->second);
                }
            }
        }
        if (asciipos.size() == 0)
        {
            num.push_back(*first);
        }
        else if (ifirst < asciipos.begin()->first)
        {
            num.push_back(*first);
        }
        else
        {
            num.append(std::to_string(asciipos.begin()->second));
        }

        if (asciirpos.size() == 0)
        {
            num.push_back(*last);
        }
        else if (ilast > asciirpos.begin()->first)
        {
            num.push_back(*last);
        }
        else
        {
            num.append(std::to_string(asciirpos.begin()->second));
        }


        nums.push_back(std::stoi(num));
        asciipos.clear();
        asciirpos.clear();
    }

    for (int i = 0; i < nums.size(); ++i)
    {
        sum += nums.at(i);
    }

    std::cout << sum;
}

void populateDigits(std::map<std::string, int>& dig)
{
    dig.emplace("zero", 0);
    dig.emplace("one", 1);
    dig.emplace("two", 2);
    dig.emplace("three", 3);
    dig.emplace("four", 4);
    dig.emplace("five", 5);
    dig.emplace("six", 6);
    dig.emplace("seven", 7);
    dig.emplace("eight", 8);
    dig.emplace("nine", 9);
}