#pragma once
#include <map>
#include <vector>

struct Round {
	int reds;
	int blues;
	int greens;
};

class Game
{
public:
	int id;
	std::vector<Round> rounds;
};