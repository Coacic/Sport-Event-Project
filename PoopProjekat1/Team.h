#ifndef _TEAM_H_
#define _TEAM_H_
#include "Competitor.h"
#include "Athlete.h"

class Team : public Competitor {
	std::vector<Athlete*> list;
public:
	Team();
	Team(int r);
	~Team();
	void pushAthlete(Athlete* ath);
	const int& getSize() const;
	Athlete* const getAthlete(int i) const;
	friend std::ostream& operator<<(std::ostream& os, const Team& a);
};

#endif // !_TEAM_H_

