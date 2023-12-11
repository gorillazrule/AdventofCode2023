#include "camelHand.h"

int camelHand::getType()
{
	std::map<int, int> cardCount;
	for (int i = 0; i < cards.size(); ++i)
	{
		cardCount[cards.at(i)]++;
	}
	bool voak = false;
	bool ivoak = false;
	bool fh = false;
	bool iiioak = false;
	int pairCount = 0;
	for (auto it = cardCount.begin(); it != cardCount.end(); ++it)
	{
		if (it->second == 5)
		{
			voak = true;
		}
		else if (it->second == 4)
		{
			ivoak = true;
		}
		else if (it->second == 3)
		{
			iiioak = true;
		}
		else if (it->second == 2)
		{
			pairCount++;
		}
	}

	if (voak)
	{
		return 7;
	}
	else if (ivoak)
	{
		return 6;
	}
	else if (iiioak && pairCount == 1)
	{
		return 5;
	}
	else if (iiioak)
	{
		return 4;
	}
	else if (pairCount == 2)
	{
		return 3;
	}
	else if (pairCount == 1)
	{
		return 2;
	}
	return 1;
}

void camelHand::setHand(std::string input)
{
	for (int i = 0; i < cards.size(); ++i)
	{
		if (isdigit(input.at(i)))
		{
			cards.at(i) = input.at(i) - '0';
		}
		else if (input.at(i) == 'T')
		{
			cards.at(i) = 10;
		}
		else if (input.at(i) == 'J')
		{
			cards.at(i) = 11;
		}
		else if (input.at(i) == 'Q')
		{
			cards.at(i) = 12;
		}
		else if (input.at(i) == 'K')
		{
			cards.at(i) = 13;
		}
		else if (input.at(i) == 'A')
		{
			cards.at(i) = 14;
		}
	}
	type = getType();
}
