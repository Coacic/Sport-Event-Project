#ifndef _COUNTRY_H_
#define _COUNTRY_H_
#include <iostream>
#include "Sport.h"

class Country {
protected:
	std::string country;

public:
	Country(std::string _country) { country = _country; };
	const std::string& getCountry() const { return country; }
};

#endif // !_COUNTRY_H_
