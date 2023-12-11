#pragma once
#include <vector>
#include <set>


class Scratchcard
{
public:
	int id;
	int copies;

	Scratchcard();
	void addWinningNumber(int n);
	void addNumber(int n);
	int calculateScore();
	int getMatches();


private:
	int score;
	int matches;
	std::multiset<int> winningNumbers;
	std::vector<int> numbers;

	int mult(int n);
};

