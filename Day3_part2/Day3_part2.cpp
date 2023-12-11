// Day3_part2.cpp :

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

//Input is size 140x141
const int M = 140;
const int N = 141;

using std::ifstream;
using std::string;
using std::vector;
using matrix = char(*)[N];



int check_gear(matrix schem, int row, int column);

int main()
{

    //Read through the inputs and put each char in a 2d array
    ifstream infile;
    infile.open("Input.txt");

    auto schematic = new char[M][N]();
    int i = 0;

    string line;
    while (getline(infile, line))
    {
        for (int j = 0; j < line.length(); ++j)
        {
            schematic[i][j] = line.at(j);
        }
        ++i;
    }
    infile.close();

    int ratio;
    vector<int> ratios;
    //Search through the schematic for potential gears
    for (int i = 0; i < M; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            if (schematic[i][j] == '*')
            {
                ratio = check_gear(schematic, i, j);

                if (ratio != 0)
                {
                    ratios.push_back(ratio);
                }
            }
        }
    }

    int sum = 0;
    for (int i = 0; i < ratios.size(); ++i)
    {
        sum += ratios.at(i);
    }

    std::cout << sum;

    delete[] schematic;
}

int check_gear(matrix schem, int row, int column)
{
    vector<int> partNums;
    bool top = false;
    bool bottom = false;
    bool left = false;
    bool right = false;
    int i = row;
    int j = column;

    //Check if the potential gear is on an edge.
    if (i - 1 < 0)
    {
        top = true;
    }

    if (i + 1 >= M)
    {
        bottom = true;
    }

    if (j - 1 < 0)
    {
        left = true;
    }

    if (j + 1 >= N)
    {
        right = true;
    }

    //Check for part to the left
    if (!left && isdigit(schem[i][j - 1]))
    {
        string partNum = "";
        int index = j - 1;
        while (index >= 0 && isdigit(schem[i][index]))
        {
            partNum = schem[i][index] + partNum;
            index--;
        }
        partNums.push_back(stoi(partNum));        
    }

    //Check for part to the right
    if (!right && isdigit(schem[i][j + 1]))
    {
        string partNum = "";
        int index = j + 1;
        while (index < N && isdigit(schem[i][index]))
        {
            partNum.push_back(schem[i][index]);
            index++;
        }
        partNums.push_back(stoi(partNum));
    }

    
    //Check row above for parts
    if (!top)
    {
        int l;
        int r;
        //Start by checking right corner, and getting the entire number
        if (!right && isdigit(schem[i - 1][j + 1]))
        {
            l = j;
            r = j + 2;
            string partNum = "";
            partNum.push_back(schem[i - 1][j + 1]);
            while (r < N && isdigit(schem[i - 1][r]))
            {
                partNum.push_back(schem[i - 1][r]);
                ++r;

            }
            while (l >= 0 && isdigit(schem[i - 1][l]))
            {
                partNum = schem[i - 1][l] + partNum;
                --l;
            }
            partNums.push_back(stoi(partNum));
        }

        //Next check the middle if on the right edge, or top right corner didn't have a digit
        if ((right && isdigit(schem[i - 1][j])) || (!right && !isdigit(schem[i - 1][j + 1]) && isdigit(schem[i - 1][j])))
        {
            l = j -1;
            string partNum = "";
            partNum.push_back(schem[i - 1][j]);
            //Only need to search for rest of number to the left because the right corner has been checked.
            while (l >= 0 && isdigit(schem[i - 1][l]))
            {
                partNum = schem[i - 1][l] + partNum;
                --l;
            }
            partNums.push_back(stoi(partNum));
        }

        //Finally check the left corner if the middle isn't a digit
        if (!left && (!isdigit(schem[i - 1][j])) && (isdigit(schem[i - 1][j - 1])))
        {
            l = j - 2;
            string partNum = "";
            partNum.push_back(schem[i - 1][j - 1]);

            while (l >= 0 && isdigit(schem[i - 1][l]))
            {
                partNum = schem[i - 1][l] + partNum;
                --l;
            }
            partNums.push_back(stoi(partNum));
        }
    }

    //Check the row below for parts
    if (!bottom)
    {
        int l;
        int r;
        if (!right && isdigit(schem[i + 1][j + 1]))
        {
            l = j;
            r = j + 2;
            string partNum = "";
            partNum.push_back(schem[i + 1][j + 1]);
            while (r < N && isdigit(schem[i + 1][r]))
            {
                partNum.push_back(schem[i + 1][r]);
                ++r;

            }
            while (l >= 0 && isdigit(schem[i + 1][l]))
            {
                partNum = schem[i + 1][l] + partNum;
                --l;
            }
            partNums.push_back(stoi(partNum));
        }

        //Next check the middle if on the right edge, or bottom right corner didn't have a digit
        if ((right && isdigit(schem[i + 1][j])) || (!right && !isdigit(schem[i + 1][j + 1]) && isdigit(schem[i + 1][j])))
        {
            l = j - 1;
            string partNum = "";
            partNum.push_back(schem[i + 1][j]);
            //Only need to search for rest of number to the left because the right corner has been checked.
            while (l >= 0 && isdigit(schem[i + 1][l]))
            {
                partNum = schem[i + 1][l] + partNum;
                --l;
            }
            partNums.push_back(stoi(partNum));
        }

        //Finally check the left corner if the middle isn't a digit
        if (!left && (!isdigit(schem[i + 1][j])) && (isdigit(schem[i + 1][j - 1])))
        {
            l = j - 2;
            string partNum = "";
            partNum.push_back(schem[i + 1][j - 1]);

            while (l >= 0 && isdigit(schem[i + 1][l]))
            {
                partNum = schem[i + 1][l] + partNum;
                --l;
            }
            partNums.push_back(stoi(partNum));
        }
    }


    //If exactly 2 parts, return the gear ratio.
    if (partNums.size() == 2)
    {
        return partNums.at(0) * partNums.at(1);
    }

    return 0;
}