// Day2_part2.cpp :


#include <iostream>
#include <fstream>
#include "Game.h"
#include <string>
#include <sstream>

using std::ifstream;
using std::string;
using std::vector;
using std::stringstream;

int main()
{
    ifstream infile;
    infile.open("Input.txt");
    string line;
    string game_id;

    vector<Game> games;


    //Read in file 1 line at a time
    while (std::getline(infile, line))
    {
        //get Game id
        line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());
        stringstream ss(line);
        game_id = "";
        Game curGame;

        string tempid;
        std::getline(ss, tempid, ':');
        string::reverse_iterator rit = tempid.rbegin();

        while (isdigit(*rit))
        {
            game_id = *rit + game_id;
            rit++;
        }

        curGame.id = std::stoi(game_id);

        //break apart into rounds
        string round;
        while (std::getline(ss, round, ';'))
        {
            Round curRound;
            curRound.blues = 0;
            curRound.greens = 0;
            curRound.reds = 0;

            stringstream ss2(round);
            string count;
            while (std::getline(ss2, count, ','))
            {

                string num = "";

                string::iterator it = count.begin();
                while (isdigit(*it))
                {
                    num.push_back(*it);
                    it++;
                }
                if (count.find("red") != string::npos)
                {
                    curRound.reds = std::stoi(num);
                }
                else if (count.find("blue") != string::npos)
                {
                    curRound.blues = std::stoi(num);
                }
                else if (count.find("green") != string::npos)
                {
                    curRound.greens = std::stoi(num);
                }

            }
            curGame.rounds.push_back(curRound);
        }
        games.push_back(curGame);
    }

    int minRed;
    int minBlue;
    int minGreen;
    vector<int> powers;

    for (int i = 0; i < games.size(); ++i)
    {
        int power;
        minRed = 0;
        minBlue = 0;
        minGreen = 0;

        for (int j = 0; j < games.at(i).rounds.size(); ++j)
        {
            Round curRound = games.at(i).rounds.at(j);
            if (curRound.reds > minRed)
            {
                minRed = curRound.reds;
            }
            if (curRound.blues > minBlue)
            {
                minBlue = curRound.blues;
            }
            if (curRound.greens > minGreen)
            {
                minGreen = curRound.greens;
            }
            
        }
        power = minRed * minBlue * minGreen;
        powers.push_back(power);
    }

    int sum = 0;
    for (int i = 0; i < powers.size(); ++i)
    {
        sum += powers.at(i);
    }

    std::cout << sum;
}