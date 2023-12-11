#include "Scratchcard.h"

Scratchcard::Scratchcard()
{
	this->score = 0;
	this->id = 0;
	this->matches = 0;
	this->copies = 1;
}

void Scratchcard::addWinningNumber(int n)
{
	winningNumbers.insert(n);
	return;
}

void Scratchcard::addNumber(int n)
{
	numbers.push_back(n);
	return;
}

int Scratchcard::calculateScore()
{
	for (int i = 0; i < numbers.size(); ++i)
	{
		if (winningNumbers.contains(numbers.at(i)))
		{
			score = mult(score);
			if (score == 0)
			{
				score = 1;
			}
		}
	}
	return score;
}

int Scratchcard::getMatches()
{
	for (int i = 0; i < numbers.size(); ++i)
	{
		if (winningNumbers.contains(numbers.at(i)))
		{
			++matches;
		}
	}
	return matches;
}

int Scratchcard::mult(int n)
{
	return n << 1;
}
