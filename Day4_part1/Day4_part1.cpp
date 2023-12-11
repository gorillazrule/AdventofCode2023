// Day4_part1.cpp :

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Scratchcard.h"

using std::ifstream;
using std::string;
using std::stringstream;
using std::vector;

int main()
{
    ifstream infile;
    infile.open("Input.txt");

    string line;
    vector<Scratchcard> cards;

    while (getline(infile, line))
    {
        Scratchcard card;
        stringstream ss(line);
        string part;
        //get card id
        getline(ss, part, ':');
        part.erase(0,4);
        part.erase(std::remove_if(part.begin(), part.end(), isspace), part.end());
        card.id = stoi(part);

        //get winning numbers
        getline(ss, part, '|');
        stringstream ss2(part);
        string num;
        while (ss2 >> num)
        {
            card.addWinningNumber(stoi(num));
        }

        //get numbers
        while (ss >> num)
        {
            card.addNumber(stoi(num));
        }

        cards.push_back(card);
    }

    infile.close();



    //Calculate the score of all the cards, and sum them
    int sum = 0;
    for (int i = 0; i < cards.size(); ++i)
    {
        sum += cards.at(i).calculateScore();
    }

    std::cout << sum;

}