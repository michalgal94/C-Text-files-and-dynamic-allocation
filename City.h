

#ifndef CITY_H_
#define CITY_H_

#include "Kindergarden.h"

#define FILE_NAME "DataFile.txt"

typedef struct {
	Kindergarden** garden;
	int numOfGardens;
}City;


void readCityFromFile(City* pCity);

int writeCityToFile(City* pCity);

void printCity(const City* pCity);

void releaseCity(City* pCity);

int addGarden(City* city, char* name);

Kindergarden* findGardenInCity(const City* city, char* gardenName);

#endif /* CITY_H_ */
