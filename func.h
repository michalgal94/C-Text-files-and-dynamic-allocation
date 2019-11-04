/*
 * func.h
 *
 *  Created on: 14 Dec 2018
 *      Author: nir
 */

#ifndef FUNC_H_
#define FUNC_H_

#define READ_CITY 1
#define SHOW_CITY 2
#define SHOW_GARDEN 3
#define WRITE_CITY 4
#define ADD_GARDEN 5
#define ADD_CHILD 6
#define CHILD_BIRTHDAY 7
#define COUNT_GRADUATE 8
#define EXIT 0

#include "City.h"

int menu();

void readCity(City* city);
void showCityGardens(City* city);
void showSpecificGardenInCity(City* city);
void saveCity(City* city);
void cityAddGarden(City* city);
void addChildToSpecificGardenInCity(City* city);
void birthdayToChild(City* city);
int countChova(City* city);

#endif /* FUNC_H_ */
