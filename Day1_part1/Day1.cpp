// Day1.cpp :


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctype.h>

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

    while (std::getline(infile, line))
    {
        string::iterator first = line.begin();
        string::reverse_iterator last = line.rbegin();
        num = "";

        while (!isdigit(*first))
        {
            first++;
        }
        num.push_back(*first);
        while (!isdigit(*last))
        {
            last++;
        }
        num.push_back(*last);
        nums.push_back(std::stoi(num));
    }

    for (int i = 0; i < nums.size(); ++i)
    {
        sum += nums.at(i);
    }

    std::cout << sum;
}

