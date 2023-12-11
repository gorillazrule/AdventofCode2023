// Day2_part1.cpp :




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

        while(isdigit(*rit))
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


    vector<int> validIds;
    for (int i = 0; i < games.size(); ++i)
    {
        bool invalid = false;
        for (int j = 0; j < games.at(i).rounds.size(); ++j)
        {
            Round curRound = games.at(i).rounds.at(j);
            if (curRound.blues > 14 || curRound.greens > 13 || curRound.reds > 12)
            {
                invalid = true;
            }
        }
        if (!invalid)
        {
            validIds.push_back(games.at(i).id);
        }
    }

    int sum = 0;
    for (int i = 0; i < validIds.size(); ++i)
    {
        sum += validIds.at(i);
    }

    std::cout << sum;
}