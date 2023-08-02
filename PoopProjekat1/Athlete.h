#ifndef _ATHLETE_H_
#define _ATHLETE_H_
#include "Competitor.h"

class Athlete : public Competitor {
	int id;
	std::string age, weight, height, name;
	char gender;

public:
	Athlete(int , std::string, std::string, std::string, std::string, std::string);
	~Athlete();
	const int& getId() const;
	const std::string& getAge() const;
	const std::string& getWeight() const;
	const std::string& getHeight() const;
	const std::string& getName() const;
	const char& getGender() const;
	friend std::ostream& operator<<(std::ostream& os, const Athlete& a);
};

#endif // !_ATHLETE_H_