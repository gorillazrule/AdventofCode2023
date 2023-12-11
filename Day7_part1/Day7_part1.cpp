// Day7_part1.cpp :

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

#include "camelHand.h"

using std::ifstream;
using std::string;
using std::stringstream;
using std::vector;

int main()
{
    ifstream infile;
    infile.open("Input.txt");

    string hand;

    vector<camelHand> hands;

    while (getline(infile, hand))
    {
        stringstream data(hand);
        string cards;
        string temp;
        int bid;
        data >> cards;
        data >> temp;
        bid = stoi(temp);

        camelHand cHand;
        cHand.bid = bid;
        cHand.setHand(cards);

        hands.push_back(cHand);
    }

    std::sort(hands.begin(), hands.end());

    //unsigned long winnings;
    int winnings = 0;

    for (int i = 0; i < hands.size(); ++i)
    {
        winnings += hands.at(i).bid * (i + 1);
    }



    std::cout << winnings;
}
