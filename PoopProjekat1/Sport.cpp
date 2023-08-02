#include "Sport.h"

std::ostream& operator<<(std::ostream& os, const Sport& s)
{
	os << s.getSport();
	return os;
}

Sport::Sport()
{
}

Sport::~Sport()
{
}

Sport::Sport(std::string _sport)
{
	sport = _sport;
}

const std::string& Sport::getSport() const
{
	return sport;
}
