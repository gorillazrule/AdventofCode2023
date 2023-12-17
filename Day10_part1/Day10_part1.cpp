// Day10_part1.cpp :

#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <vector>
#include <queue>
#include "matrix.h"

using std::ifstream;
using std::string;
using std::pair;
using std::vector;
using std::queue;

struct coord
{
    int x;
    int y;
};

enum direction { up, down, left, right };

struct unit
{
    coord location;
    direction dir;

};


bool connects(coord current, coord potential, char c);

std::pair<unit, int> setWeight(unit u, matrix<int>& weights, matrix<char>& map);

coord getNext(coord start, direction dir);


int main()
{
    ifstream infile;
    infile.open("Input.txt");

    string line;
    matrix<char> map;
    coord start;
    start.x = -1;
    start.y = -1;

    //put all the input into matrix, and keep track of where the starting position is
    while (getline(infile, line))
    {
        vector<char> temp;
        if (map.getWidth() == 0)
        {
            map.setWidth(line.size());
        }
        for (int i = 0; i < line.size(); ++i)
        {
            if (line.at(i) == 'S')
            {
                start.x = i;
            }
            temp.push_back(line.at(i));
        }
        map.addElements(temp);

        if (start.y == -1 && start.x != -1)
        {
            start.y = map.getHeight() - 1;
        }
    }

    infile.close();

    //Initialize a matrix of the same size of map, and fill it with weight of -1, then set the starting point weight to 0
    matrix<int> weights(map.getWidth(), map.getHeight(), -1);
    weights.set(start.x, start.y, 0);

    //Check the 4 cardinal directions for valid pipes
    queue<unit> next;
    coord up = { start.x,start.y - 1 };
    coord down = { start.x,start.y + 1 };
    coord left = { start.x - 1,start.y };
    coord right = { start.x + 1, start.y };

    if (connects(start, up, map.at(up.x, up.y)))
    {
        next.push(unit {up,direction::down});
        weights.set(up.x,up.y, 1);
    }
    if (connects(start, down, map.at(down.x,down.y)))
    {
        next.push(unit {down, direction::up});
        weights.set(down.x, down.y, 1);
    }
    if (connects(start, left, map.at(left.x, left.y)))
    {
        next.push(unit {left, direction::right});
        weights.set(left.x, left.y, 1);
    }
    if (connects(start, right, map.at(right.x, right.y)))
    {
        next.push(unit {right, direction::left});
        weights.set(right.x, right.y, 1);
    }

    int maxWeight;
   
    while (next.size() != 0)
    {
        //Get the first element and check which symbol it is. Based upon the symbol and the direction you came from, set the weight for the 
        //next pipe if it does not already have one.
        unit check = next.front();
        next.pop();

        pair<unit, int> result = setWeight(check, weights, map);

        if (result.second == -1)
        {
            next.push(result.first);
        }
        else
        {
            std::cout << result.second << std::endl;
            break;
        }

    }

}

bool connects(coord current, coord potential, char c)
{
    if (potential.x < current.x)
    {
        if (c == 'L' || c == 'F' || c == '-')
        {
            return true;
        }
    }
    else if (potential.x > current.x)
    {
        if (c == 'J' || c == '7' || c == '-')
        {
            return true;
        }
    }
    else if (potential.y < current.y)
    {
        if (c == 'F' || c == '7' || c == '|')
        {
            return true;
        }
    }
    else if (potential.y > current.y)
    {
        if (c == 'J' || c == 'L' || c == '|')
        {
            return true;
        }
    }
    return false;
}

std::pair<unit, int> setWeight(unit u, matrix<int>& weights, matrix<char>& map)
{
    coord checkCoord = u.location;
    direction checkDirection = u.dir;
    coord temp;
    direction nextDir;
    int maxWeight = -1;
    int weight;
    coord nextCoord;

    switch (map.at(checkCoord.x, checkCoord.y))
    {
        case '|':
            switch (checkDirection)
            {
                case direction::up:
                    nextCoord = getNext(checkCoord, direction::down);
                    nextDir = direction::up;
                    break;
                case direction::down:
                    nextCoord = getNext(checkCoord, direction::up);
                    nextDir = direction::down;
                    break;
                default:
                    std::cout << "Error in setWeight with symbol: | at location: " << checkCoord.x << ", " << checkCoord.y << std::endl;
                    break;

            }
            break;
        case '-':
            switch (checkDirection)
            {
                case direction::left:
                    nextCoord = getNext(checkCoord, direction::right);
                    nextDir = direction::left;
                    break;
                case direction::right:
                    nextDir = direction::right;
                    nextCoord = getNext(checkCoord, direction::left);
                    break;
                default:
                    std::cout << "Error in setWeight with symbol: - at location: " << checkCoord.x << ", " << checkCoord.y << std::endl;
                    break;
            }
            break;
        case 'J':
            switch (checkDirection)
            {
                case direction::up:
                    nextCoord = getNext(checkCoord, direction::left);
                    nextDir = direction::right;
                    break;
                case direction::left:
                    nextCoord = getNext(checkCoord, direction::up);
                    nextDir = direction::down;
                    break;
                default:
                    std::cout << "Error in setWeight with symbol: J at location: " << checkCoord.x << ", " << checkCoord.y << std::endl;
                    break;
            }
            break;
        case 'L':
            switch (checkDirection)
            {
                case direction::up:
                    nextCoord = getNext(checkCoord, direction::right);
                    nextDir = direction::left;
                    break;
                case direction::right:
                    nextCoord = getNext(checkCoord, direction::up);
                    nextDir = direction::down;
                    break;
                default:
                    std::cout << "Error in setWeight with symbol: L at location: " << checkCoord.x << ", " << checkCoord.y << std::endl;
                    break;
            }
            break;
        case 'F':
            switch (checkDirection)
            {
                case direction::down:
                    nextCoord = getNext(checkCoord, direction::right);
                    nextDir = direction::left;
                    break;
                case direction::right:
                    nextCoord = getNext(checkCoord, direction::down);
                    nextDir = direction::up;
                    break;
                default:
                    std::cout << "Error in setWeight with symbol: F at location: " << checkCoord.x << ", " << checkCoord.y << std::endl;
                    break;

            }
            break;
        case '7':
            switch (checkDirection)
            {
                case direction::left:
                    nextCoord = getNext(checkCoord, direction::down);
                    nextDir = direction::up;
                    break;
                case direction::down:
                    nextCoord = getNext(checkCoord, direction::left);
                    nextDir = direction::right;
                    break;
                default:
                    std::cout << "Error in setWeight with symbol: 7 at location: " << checkCoord.x << ", " << checkCoord.y << std::endl;
                    break;
            }
            break;
        default:
            std::cout << "Error in setWeight with unknown symbol: " << map.at(checkCoord.x, checkCoord.y) << " at location : " << checkCoord.x << ", " << checkCoord.y << std::endl;
            break;
    }

    if (weights.at(nextCoord.x, nextCoord.y) != -1)
    {
        maxWeight = (weights.at(checkCoord.x, checkCoord.y) > weights.at(nextCoord.x,nextCoord.y))? weights.at(checkCoord.x,checkCoord.y) : weights.at(nextCoord.x,nextCoord.y);
    }
    else
    {
        int prevWeight = weights.at(checkCoord.x, checkCoord.y);
        weights.set(nextCoord.x, nextCoord.y, prevWeight + 1);
    }

    return std::make_pair(unit{ nextCoord,nextDir }, maxWeight);
}

coord getNext(coord start, direction dir)
{
    switch (dir)
    {
        case direction::up:
            return coord{ start.x, start.y - 1 };
        case direction::down:
            return coord{ start.x, start.y + 1 };
        case direction::left:
            return coord{ start.x - 1, start.y };
        case direction::right:
            return coord{ start.x + 1, start.y };
    }
}
