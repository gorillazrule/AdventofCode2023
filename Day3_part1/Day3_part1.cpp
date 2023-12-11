// Day3_part1.cpp :

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>

using std::ifstream;
using std::string;
using std::vector;
using std::pair;
using matrix = char(*)[141];

struct result
{
    int row;
    int column;
    bool valid;
    string partNum;
};

bool isSpecial(char character);
result checkIfPart(matrix schem, int row, int column);


int main()
{
    //Read through the inputs and put each char in a 2d array
    ifstream infile;
    infile.open("Input.txt");

    auto schematic = new char[140][141]();
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

    vector<int> parts;

    //Loop through matrix and check for parts.
    for (int i = 0; i < 140; ++i)
    {
        for (int j = 0; j < 141; ++j)
        {
            if (isdigit(schematic[i][j]))
            {
                result after;
                after = checkIfPart(schematic, i, j);
                i = after.row;
                j = after.column;
                if (after.valid)
                {
                    parts.push_back(stoi(after.partNum));
                }
            }
        }
    }

    int sum = 0;
    for (int i = 0; i < parts.size(); ++i)
    {
        sum += parts.at(i);
    }
    std::cout << sum;

    delete[] schematic;
}

bool isSpecial(char character)
{
    if (isdigit(character) || character == '.' || character == '\0')
    {
        return false;
    }
    return true;
}

result checkIfPart(matrix schem, int row, int column)
{
    bool isPart = false;
    bool complete = false;
    int i = row;
    int j = column;
    string number = "";
    bool top = false;
    bool bottom = false;
    bool left = false;
    bool right = false;

    //Check boundaries to make sure we don't try to access array out of bounds
    if (i - 1 < 0)
    {
        top = true;
    }
    if (i + 1 >= 139)
    {
        bottom = true;
    }
    if (j - 1 < 0)
    {
        left = true;
    }
    
    //Run until the full number has been recorded.
    while (!complete)
    {
        //Since j is constantly moving from left to right we need to recheck this boundary every loop.
        if (j + 1 >= 140)
        {
            right = true;
        }

        //append the current digit onto number
        number.push_back(schem[i][j]);

        //Only check surroundings if a special character has not been discovered yet.
        if (!isPart)
        {
            //Check the character above and below current digit
            if (!top && isSpecial(schem[i - 1][j]))
            {
                isPart = true;
            }
            else if (!bottom && isSpecial(schem[i + 1][j]))
            {
                isPart = true;
            }

            //If it is the first digit, check the previous column
            else if (j == column && !left)
            {
                if (isSpecial(schem[i][j - 1]))
                {
                    isPart = true;
                }
                else if (!top && isSpecial(schem[i - 1][j - 1]))
                {
                    isPart = true;
                }
                else if (!bottom && isSpecial(schem[i + 1][j - 1]))
                {
                    isPart = true;
                }

            }

            //If it is the last digit check the next column
            if (!right && !isdigit(schem[i][j+1]))
            {
                if (isSpecial(schem[i][j + 1]))
                {
                    isPart = true;
                }
                else if (!top && isSpecial(schem[i - 1][j + 1]))
                {
                    isPart = true;
                }
                else if (!bottom && isSpecial(schem[i + 1][j + 1]))
                {
                    isPart = true;
                }
            }

        }

        //Check if end of column/ next cell isn't number
        if (right)
        {
            i++;
            j = 0;
            complete = true;
        }
        else if (!isdigit(schem[i][j + 1]))
        {
            complete = true;
            ++j;
        }
        else
        {
            ++j;
        }
    }

    //Construct result and return it
    result answer;
    answer.row = i;
    answer.column = j;
    answer.partNum = number;
    answer.valid = isPart;
    return answer;
}
