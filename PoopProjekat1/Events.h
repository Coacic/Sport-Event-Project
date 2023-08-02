#ifndef _EVENTS_H_
#define _EVENTS_H_
#include "Team.h"

class Events {
	std::string date, city, cup, type, reward;
	Athlete* athlete;
	Team* team;
	Sport* sport;
	Country* country;

public:
	Events(std::string _date, std::string _city, Sport* _sport, std::string _cup, std::string _type, Country * country, std::string _reward, Athlete* _athlete, Team* _team);
	~Events();
	const std::string& getDate() const;
	const std::string& getCity() const;
	const Sport& getSport() const;
	const Country& getCountry() const;
	const std::string& getCup() const;
	const std::string& getType() const;
	const std::string& getTeamName() const;
	const std::string& getReward() const;
	const Athlete& getAthlete() const;
	const Team& getTeam() const;
	friend std::ostream& operator<<(std::ostream& os, const Events& e);
};

#endif // !_EVENTS_H_