#include "Team.h"

Team::Team()
{
}

Team::Team(int r)
{
	list.reserve(r);
}

Team::~Team()
{
	list.~vector();
}

void Team::pushAthlete(Athlete* ath)
{
	list.push_back(ath);
}

const int& Team::getSize() const
{
	return static_cast<int>(list.size());
}

Athlete* const Team::getAthlete(int i) const
{
	auto iter = list.begin();
	std::advance(iter, i);
	return *iter;
}

std::ostream& operator<<(std::ostream& os, const Team& a)
{
	for (int i = 0; i < a.getSize(); i++)
	{
		os << (*a.getAthlete(i)) << std::endl;
	}
	return os;
}