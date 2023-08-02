#include "Events.h"

Events::Events(std::string _date, std::string _city, Sport* _sport, std::string _cup, std::string _type, Country* _country, std::string _reward, Athlete* _athlete, Team* _team)
{
	date = _date;
	city = _city;
	cup = _cup;
	type = _type;
	reward = _reward;
	Events::athlete = _athlete;
	Events::team = _team;
	Events::country = _country;
	Events::sport = _sport;
}

Events::~Events()
{
}

const std::string& Events::getDate() const
{
	return date;
}

const std::string& Events::getCity() const
{
	return city;
}

const Sport& Events::getSport() const
{
	return *sport;
}

const std::string& Events::getCup() const
{
	return cup;
}

const Country& Events::getCountry() const
{
	return *country;
}

const std::string& Events::getReward() const
{
	return reward;
}

const Athlete& Events::getAthlete() const
{
	return *athlete;
}

const Team& Events::getTeam() const
{
	return *team;
}

std::ostream& operator<<(std::ostream& os, const Events& e)
{
	if (e.team)
	{
		os << "(*)Tim:\n" << e.getTeam();
		if (e.athlete)
			os << (* e.athlete);
		os << e.getDate() << " " << e.getCity() << " " << e.getSport().getSport() << " " << e.getCup() << " " << e.getCountry().getCountry() << " " << e.getReward();
	}
	else if (e.athlete)
	{
		os << "(-)Atleta: " << e.getAthlete() << " " << e.getDate() << " " << e.getCity() << " " << e.getSport().getSport()
			<< " " << e.getCup() << " " << e.getCountry().getCountry() << " " << e.getReward();

	}
	return os;
}