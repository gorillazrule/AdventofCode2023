#pragma once
#include <vector>
#include <string>
#include <map>
class camelHand
{
private:
	std::vector<int> actualCards;
	std::vector<int> jokerCards;
	int type;

	std::pair<int,int> getType(std::vector<int> &hand);
	void setJokers();

public:
	int bid;

	camelHand() : actualCards(5, 0), jokerCards(5, 0), bid(0), type(0) {}

	void setHand(std::string input);

	friend constexpr auto operator<=>(const camelHand& l, const camelHand& r)
	{
		//Compare type
		if (auto c = l.type <=> r.type; !std::is_eq(c))
		{
			return c;
		}
		//Compare cards in order from left to right
		for (int i = 0; i < 5; ++i)
		{
			if (auto c = l.actualCards.at(i) <=> r.actualCards.at(i); !std::is_eq(c))
			{
				return c;
			}
		}
		return l.bid <=> r.bid;
	}

	friend bool operator==(const camelHand&, const camelHand&) = default;
};

