#ifndef _GAMES_H_
#define _GAMES_H_
#include <iostream>
#include <vector>

class Games {
private:
	std::vector<std::string> games;

public:
	Games();
	~Games();
	int push(std::string _games);
	const std::string& getGames(int index) const;
	int contains(std::string str, std::vector<std::string>::iterator it);
	friend std::ostream& operator<<(std::ostream& os, const Games& g);
	const int getSize() const;
};

#endif // !_GAMES_H_
