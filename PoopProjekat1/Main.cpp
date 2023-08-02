#include <algorithm>
#include <regex>
#include <sstream>
#include <fstream>
#include <chrono>
#include "Events.h"
#include "Games.h"
#include "Sport.h"
#include "GAthleteDoesNotExist.h"
#include "GTeamDoesNotExist.h"

Athlete* parseAthletes(const std::string str, std::smatch& match, std::regex& rgx)
{
	if (std::regex_search(str.begin(), str.end(), match, rgx))
	{
		return new Athlete(std::stoi(match[1]), match[4], match[6], match[5], match[2], match[3].str());
	}
}

void parseTeam(std::string str, std::vector<int>* list)
{
	int i = 0;
	int num = 0;
	char c = str[i];
	while (c != '\0')
	{
		if (isdigit(c)) {
			num = num * 10 + (c - '0');
		}
		else if (c == ',') {
			(*list).emplace_back(num);
			num = 0;
		}
		c = str[++i];
	}
	return;
}

Events* parseEvents(const std::string& str, std::vector<Athlete*>* listofAthletes, std::vector<Country*>* listOfCountries, std::vector<Sport*>* listOfSports, Games* games, std::vector<int>::iterator& it2, std::vector<Country*>::iterator& it3, std::vector<Athlete*>::iterator& it, std::vector<Sport*>::iterator& it4, std::vector<std::string>::iterator& it5, std::vector<int>& listOfAthletesIds, Athlete* ath, Country* country, Sport* sport, Team* teamOfPlayersList, std::smatch& match, std::regex& rgx, int& id, std::stringstream& ids, int& index, std::ofstream& out, std::string& tmp)
{
	try {
		if (std::regex_search(str.begin(), str.end(), match, rgx))
		{
			listOfAthletesIds.clear();
			ath = nullptr;
			if (match[5].str() == "Individual")
			{
				id = std::stoi(match[7]);
				it = std::find_if((*listofAthletes).begin(), (*listofAthletes).end(), [&id](Athlete* x) { return x->getId() == id; });
				ath = *it;
			}
			else
			{
				parseTeam(match[7].str(), &listOfAthletesIds);
				teamOfPlayersList = new Team(listOfAthletesIds.size());
				for (it2 = listOfAthletesIds.begin(); it2 != listOfAthletesIds.end(); it2++)
				{
					it = std::find_if((*listofAthletes).begin(), (*listofAthletes).end(), [&it2](Athlete* x) { return x->getId() == *it2; });
					teamOfPlayersList->pushAthlete(*it);
				}
				it = (*listofAthletes).end();
			}
			it3 = std::find_if((*listOfCountries).begin(), (*listOfCountries).end(), [&](Country* x) {return x->getCountry() == match[6]; });
			if (it3 == (*listOfCountries).end()) {
				country = new Country(match[6]);
				(*listOfCountries).emplace_back(country);
			}
			else
				country = *it3;
			it4 = std::find_if((*listOfSports).begin(), (*listOfSports).end(), [&](Sport* x) {return x->getSport() == match[3]; });
			if (it4 == (*listOfSports).end()) {
				sport = new Sport(match[3]);
				(*listOfSports).emplace_back(sport);
			}
			else
				sport = *it4;
			if ((index = games->contains(match[3].str(), it5) == -1))
				index = games->push(match[3].str());
			return new Events(match[1], match[2], sport, games->getGames(index), match[5], country, match.suffix(), ath, teamOfPlayersList);
		}
	}
	catch (std::exception e)
	{
		return nullptr;
	}
	return nullptr;
}

int main()
{
	int op = -1, isDataLoaded1 = 0, isDataLoaded2 = 0, n = 0, count = 0;
	std::ifstream fileAth("C:\\Users\\Coca\\Desktop\\Projekti\\CPP\\source\\repos\\PoopProjekat1\\PoopProjekat1\\athletes.txt");
	std::ifstream fileEve("C:\\Users\\Coca\\Desktop\\Projekti\\CPP\\source\\repos\\PoopProjekat1\\PoopProjekat1\\events.txt");
	std::ofstream in("out.txt");
	std::ofstream outAth("outAth.txt");
	std::ofstream outEve("outEve.txt");
	FILE* fileEveC = fopen("C:\\Users\\Coca\\Desktop\\Projekti\\CPP\\source\\repos\\PoopProjekat1\\PoopProjekat1\\events.txt", "r");
	FILE* fileAthC = fopen("C:\\Users\\Coca\\Desktop\\Projekti\\CPP\\source\\repos\\PoopProjekat1\\PoopProjekat1\\athletes.txt", "r");
	int linesAth = 0;
	int linesEve = 0;
	std::string line;
	std::chrono::high_resolution_clock::time_point begin;
	std::chrono::high_resolution_clock::time_point end;
	std::chrono::high_resolution_clock::time_point end2;
	begin = std::chrono::high_resolution_clock::now();
	for (linesAth = 0; std::getline(fileAth, line); linesAth++);
	end = std::chrono::high_resolution_clock::now();
	for (linesEve = 0; std::getline(fileEve, line); linesEve++);
	end2 = std::chrono::high_resolution_clock::now();
	fileAth.close(); fileEve.close();
	std::vector<Events*> listOfEvents;
	listOfEvents.reserve(linesEve);
	std::vector<Country*> listOfCountries;
	std::vector<Sport*> listOfSports;
	Games* games = new Games();
	std::string buff;
	std::vector<Events*>::iterator itEnd;
	std::vector<int>::iterator it2;
	std::vector<Country*>::iterator it3;
	std::vector<Athlete*>::iterator it;
	std::vector<Sport*>::iterator it4;
	std::vector<std::string>::iterator it5;
	std::string game;
	std::vector<int> listOfAthletesIds;
	std::stringstream ids;
	Athlete* ath = nullptr;
	Country* country = nullptr;
	Sport* sport = nullptr;
	Team* teamOfPlayersList = nullptr;
	std::string x3;
	int id;
	int index = -1;
	std::vector<Athlete*> listOfAthletes;
	listOfAthletes.reserve(linesAth);
	char bufferInAth[128];
	char bufferInEve[512];
	std::smatch match;
	std::string str;
	std::regex rgx("([0-9]*)!([^!]*)!([MF]|NA)!([0-9]*|NA*)!([0-9]*|NA*)!([0-9]*|NA)");
	std::regex rgx2("([^!]*)!([^!]*)!([^!]*)!([^!]*)!([^!]*)!([^!]*)!([^!]*)!(\\w*)");

	while (1) {
		std::cout << "\n-------------------------------------------------------------\nUnesite opciju:\n0. Exit\n1. Unos podataka\n2. Ispis podataka atleta\n3. Ucitavanje podataka eventova\n4. Ispis podataka eventova\n-------------------------------------------------------------\n";
		std::cin >> op;
		switch (op)
		{
		case 0:
			for (auto const& i : listOfAthletes)
				i->~Athlete();
			for (auto const& i : listOfCountries)
				i->~Country();
			for (auto const& i : listOfEvents)
				i->~Events();
			for (auto const& i : listOfSports)
				i->~Sport();
			for (auto const& i : listOfSports)
				i->~Sport();
			games->~Games();
			listOfAthletesIds.~vector();
			in.close();
			fclose(fileEveC); fclose(fileAthC);
			outEve.close(); outAth.close(); in.close();
			std::cout << "Program uspesno zavrsen";
			exit(0);

		case 1:
			std::cout << "Unos podataka je u toku za athlete";
			begin = std::chrono::high_resolution_clock::now();
			memset(bufferInAth, 0, sizeof(bufferInAth));
			bufferInAth[127] = '\0';
			count = 0;
			while (fgets(bufferInAth, sizeof bufferInAth, fileAthC) != NULL)
				listOfAthletes.emplace_back(parseAthletes(bufferInAth, match, rgx));
			std::cout << "\nPodaci uspesno ucitani";
			isDataLoaded1 = 1;
			end = std::chrono::high_resolution_clock::now();
			std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::seconds> (end - begin).count() << "s" << std::endl;
			break;
		case 2:
			if (!isDataLoaded1)
			{
				std::cout << "Unesite podatke atleta prvo";
				break;
			}
			begin = std::chrono::high_resolution_clock::now();
			std::cout << "Unesite koliko linija zelite da se istampa:\n";
			std::cin >> n;
			count = 0;
			for (auto const& i : listOfAthletes)
			{
				std::cout << (*i) << std::endl;
				if (++count == n)
					break;
			}
			end = std::chrono::high_resolution_clock::now();
			std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::seconds> (end - begin).count() << "s" << std::endl;
			break;

		case 3:
			std::cout << "Unos podataka je u toku za eventove";
			begin = std::chrono::high_resolution_clock::now();
			memset(bufferInEve, 0, sizeof(bufferInEve));
			bufferInEve[511] = '\0';
			count = 0;
			while (fgets(bufferInEve, sizeof bufferInEve, fileEveC) != NULL)
			{
				listOfEvents.emplace_back(parseEvents(bufferInEve, &listOfAthletes, &listOfCountries, &listOfSports, games, it2, it3, it, it4, it5, listOfAthletesIds, ath, country, sport, teamOfPlayersList, match, rgx2, id, ids, index, in, x3));
				if (++count == 5000)
					break;
			}
			std::cout << "\nPodaci uspesno ucitani";
			isDataLoaded2 = 1;
			end = std::chrono::high_resolution_clock::now();
			std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::seconds> (end - begin).count() << "s" << std::endl;
			break;

		case 4:
			if (!isDataLoaded1 || !isDataLoaded2)
			{
				std::cout << "Unesite podatke atleta i eventova prvo!" << std::endl;
				break;
			}
			std::cout << "Unesite koliko linija zelite da se istampa:\n";
			std::cin >> n;
			begin = std::chrono::high_resolution_clock::now();
			itEnd = listOfEvents.begin();
			std::advance(itEnd, n);
			for (auto it = listOfEvents.begin(); it != itEnd; it++)
				std::cout << (**it) << std::endl;
			end = std::chrono::high_resolution_clock::now();
			std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::seconds> (end - begin).count() << "s" << std::endl;
			break;

		case 5:
			if (!isDataLoaded1)
			{
				std::cout << "Unesite podatke atleta prvo";
				break;
			}
			begin = std::chrono::high_resolution_clock::now();
			for (auto const& i : listOfAthletes)
			{
				outAth << (*i) << std::endl;
			}
			end = std::chrono::high_resolution_clock::now();
			std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::seconds> (end - begin).count() << "s" << std::endl;
			break;

		case 6:
			if (!isDataLoaded1 || !isDataLoaded2)
			{
				std::cout << "Unesite podatke atleta i eventova prvo!" << std::endl;
				break;
			}
			begin = std::chrono::high_resolution_clock::now();
			for (auto const& i : listOfEvents)
			{
				outEve << (*i) << std::endl;
			}
			end = std::chrono::high_resolution_clock::now();
			std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::seconds> (end - begin).count() << "s" << std::endl;
			break;

		default:
			std::cout << "Odabrana opcija ne postoji, izaberite ponovo.";
			break;
		}
	}
}