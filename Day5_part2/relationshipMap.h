#pragma once
#include <compare>
class relationshipMap
{
public:
	long long destination;
	long long source;
	long long range;

	relationshipMap() :destination(0), source(0), range(0) {}
	long long checkRange(long long id);

	friend constexpr auto operator<=> (const relationshipMap& l, const relationshipMap& r)
	{
		if (auto c = l.source <=> r.source; !std::is_eq(c))
		{
			return c;
		}
		return l.destination <=> r.destination;
	};

	friend bool operator==(const relationshipMap&, const relationshipMap&) = default;


};

