#include "camelHand.h"

std::pair<int,int> camelHand::getType(std::vector<int> &hand)
{
	std::map<int, int> cardCount;
	for (int i = 0; i < hand.size(); ++i)
	{
		cardCount[hand.at(i)]++;
	}
	bool voak = false;
	bool ivoak = false;
	bool fh = false;
	bool iiioak = false;
	int pairCount = 0;

	std::pair<int, int> win;
	for (auto it = cardCount.begin(); it != cardCount.end(); ++it)
	{
		//Five of a kind
		if (it->second == 5)
		{
			return std::make_pair(7, it->first);

		}
		//Four of a kind
		else if (it->second == 4)
		{
			return std::make_pair(6, it->first);
		}
		//Three of a kind
		else if (it->second == 3)
		{
			iiioak = true;
			win.first = 4;
			win.second = it->first;
		}
		else if (it->second == 2)
		{
			win.second = it->first;
			pairCount++;
		}
	}

	if (iiioak && pairCount == 1)
	{
		win.first = 5;
		return win;
	}
	else if (iiioak)
	{
		return win;
	}
	else if (pairCount == 2)
	{
		win.first = 3;
		return win;
	}
	else if (pairCount == 1)
	{
		win.first = 2;
		return win;
	}

	win.first = 1;
	win.second = cardCount.begin()->first;
	return win;
}

void camelHand::setJokers()
{
	int jokerCount = 0;
	std::vector<int> jokerless = actualCards;
	for (int i = 0; i < jokerless.size(); ++i)
	{
		if (jokerless.at(i) == 1)
		{
			++jokerCount;
		}
	}
	jokerless.erase(std::remove_if(jokerless.begin(), jokerless.end(), [](const int i) {return i == 1;}), jokerless.end());
	if (jokerCount == 0)
	{
		jokerCards = actualCards;
		return;
	}
	else if (jokerCount == 5)
	{
		jokerCards = std::vector<int>(5, 14);
		return;
	}
	else
	{
		std::pair<int, int> typePair = getType(jokerless);
		for (int i = 0; i < jokerCount; ++i)
		{
			jokerless.push_back(typePair.second);
		}
	}
	jokerCards = jokerless;
	return;

}

void camelHand::setHand(std::string input)
{
	for (int i = 0; i < actualCards.size(); ++i)
	{
		if (isdigit(input.at(i)))
		{
			actualCards.at(i) = input.at(i) - '0';
		}
		else if (input.at(i) == 'T')
		{
			actualCards.at(i) = 10;
		}
		else if (input.at(i) == 'J')
		{
			actualCards.at(i) = 1;
		}
		else if (input.at(i) == 'Q')
		{
			actualCards.at(i) = 12;
		}
		else if (input.at(i) == 'K')
		{
			actualCards.at(i) = 13;
		}
		else if (input.at(i) == 'A')
		{
			actualCards.at(i) = 14;
		}
	}

	setJokers();
	type = getType(jokerCards).first;
}
