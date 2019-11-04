
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "City.h"


void readCityFromFile(City* pCity)
{
	int i;
	FILE* file = fopen(FILE_NAME, "r");
	if(file == NULL)
	{
		printf("Failed to open file");
		return;
	}
	if(pCity->garden) //if is not first run, release before reading again.
	{
		releaseCity(pCity);
	}
	fscanf(file, "%d", &pCity ->numOfGardens);
	pCity->garden = (Kindergarden**)malloc(pCity->numOfGardens*sizeof(Kindergarden*));
	// create in the city array of gardens
	if(!pCity->garden)
		return;
	//for each garden, read garden from file.
	for(i = 0; i < pCity->numOfGardens; i++)
	{
		pCity->garden[i] = (Kindergarden*)malloc(1*sizeof(Kindergarden));
		if(!pCity->garden[i])
			return;
		readGardenFromFile(pCity->garden[i], file);
	}
	fclose(file);
}

int writeCityToFile(City* pCity)
{
	int i;
	FILE* file;
	file = fopen(FILE_NAME, "w");
	if(!file)
		return -1;
	fprintf(file, "%d\n", pCity->numOfGardens);
	for (i = 0; i < pCity->numOfGardens; i++)
		writeGardenToFile(pCity->garden[i], file);
	fclose(file);
	return 0;
}

void printCity(const City* pCity)
{
	int i;
	printf("There are %d kinder gardens in the city.\n", pCity->numOfGardens);
	for(i = 0; i < pCity->numOfGardens; i++)
	{
		printf("\nKindergarten %d:\n", (i+1));
		printGarden(pCity->garden[i]);
	}
}

void releaseCity(City* pCity)
{
	int i;
	for (i = 0; i < pCity->numOfGardens; i++)
	{
		releaseGarden(pCity->garden[i]);
		free(pCity->garden[i]);
	}
	free(pCity->garden);
}

int addGarden(City* city, char* name)
{
	int i;
	for(i = 0; i < city->numOfGardens; i++)
		if(strcmp(city->garden[i]->name ,name) == 0)
			return -2;

	city->garden= (Kindergarden**)realloc(city->garden, sizeof(Kindergarden*)*(city->numOfGardens + 1));
	if(city->garden == NULL)
		return -1;

	city->garden[city->numOfGardens] = (Kindergarden*)malloc(1*sizeof(Kindergarden));
	if(city->garden[city->numOfGardens] == NULL)
		return -1;

	initGarden(city->garden[city->numOfGardens], name);
	city->numOfGardens++;
	return 0;
}

Kindergarden* findGardenInCity(const City* city, char* gardenName)
{
	int i;
	for(i = 0; i < city->numOfGardens; i++)
		if(strcmp(city->garden[i]->name ,gardenName) == 0)
			return city->garden[i];
	return NULL;
}
