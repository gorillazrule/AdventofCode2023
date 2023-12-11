#pragma once
#include <compare>

class seedInfo
{

public:
	long long seed = -1;
	long long soil = -1;
	long long fertilizer = -1;
	long long water = -1;
	long long light = -1;
	long long temperature = -1;
	long long humidity = -1;
	long long location = -1;

	seedInfo() = default;

	friend constexpr std::strong_ordering operator<=>(const seedInfo& l, const seedInfo& r)
	{
		if (auto c = l.location <=> r.location; !std::is_eq(c))
		{
			return c;
		}
		return l.seed <=> r.seed;
	};

	friend bool operator==(const seedInfo&, const seedInfo&) = default;

};

