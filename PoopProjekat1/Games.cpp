#include "Games.h"

Games::Games()
{
}

Games::~Games()
{
	games.~vector();
}

int Games::push(std::string _games)
{
	games.push_back(_games);
	return getSize()-1;
}

const std::string& Games::getGames(int index) const
{
	return games[index];
}

int Games::contains(std::string str, std::vector<std::string>::iterator it)
{
	it = std::find(games.begin(), games.end(), str);
	if (it != games.end())
		return games.end() - it;
	return -1;
}

const int Games::getSize() const
{
	return games.size();
}

std::ostream& operator<<(std::ostream& os, const Games& g)
{
	for (std::string var : g.games)
	{
		os << var << "\n";
	}
	return os;
}
