#ifndef _SPORT_H_
#define	_SPORT_H_
#include <iostream>

class Sport {
	std::string sport;

public:
	Sport();
	~Sport();
	Sport(std::string _sport);
	const std::string& getSport() const;
	friend std::ostream& operator<<(std::ostream& os, const Sport& s);
};

#endif // !_SPORT_H_
