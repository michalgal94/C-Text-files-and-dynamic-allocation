
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "func.h"
#include "City.h"


int menu()
{
	int option;

	printf("\n==========================\n");
	printf("Select:\n\n");
	printf("\t%d. Read city information from file.\n", READ_CITY);
	printf("\t%d. Show all kindergartens.\n", SHOW_CITY);
	printf("\t%d. Show a specific kindergarten.\n", SHOW_GARDEN);
	printf("\t%d. Save city information to file.\n", WRITE_CITY);
	printf("\t%d. Add a kindergarten.\n", ADD_GARDEN);
	printf("\t%d. Add a child.\n", ADD_CHILD);
	printf("\t%d. Birthday to a child.\n", CHILD_BIRTHDAY);
	printf("\t%d. Count Preschool children.\n", COUNT_GRADUATE);
	printf("\t%d. Exit.\n", EXIT);

	scanf("%d", &option);
	return option;
}

void readCity(City* city)
{
	readCityFromFile(city);
}

void showCityGardens(City* city)
{
	printCity(city);
}

void showSpecificGardenInCity(City* city)
{
	int i, isFound = 0;
	char searchName[100];

	printf("Enter garden name to show: \n");
	getchar();
	fgets(searchName,100,stdin);
	searchName[strcspn(searchName, "\n")] = '\0';

	for(i = 0; i < city->numOfGardens; i++)
	{
		if(strcmp(searchName,city->garden[i]->name) == 0)
		{
			printGarden(city->garden[i]);
			isFound = 1;
		}
	}
	if(!isFound)
		printf("No garden by this name.\n");
}

void saveCity(City* city)
{
	int isWritten;
	isWritten = writeCityToFile(city);
	if(isWritten == -1)
		printf("Could not open file.");
	else if(isWritten == 0)
		printf("City has been saved to file successfully.\n");
}

void cityAddGarden(City* city)
{
	char gardenNameToAdd[GARDEN_NAME_LENGTH];
	printf("Enter garden name to add: \n");
	scanf("%s", gardenNameToAdd);

	Kindergarden* garden = findGardenInCity(city, gardenNameToAdd);
	if(garden == NULL)
	{
		if(addGarden(city, gardenNameToAdd) == 0)
		{
			printf("Garden added successfully\n");
			return;
		}
	}
	if(addGarden(city, gardenNameToAdd) == -2)
	{
		printf("Garden %s already exist\n", gardenNameToAdd);
		cityAddGarden(city);
	}
}

void addChildToSpecificGardenInCity(City* city)
{
	int i, id;
	char wantedGarden[GARDEN_NAME_LENGTH];
	printf("Enter garden name: \n");
	scanf("%s", wantedGarden);
	for (i = 0; i < city->numOfGardens; i++)
	{
		if (strcmp(wantedGarden, city->garden[i]->name) == 0)
		{
			do
			{
				printf("Enter child's ID to add: \n");
				scanf("%d", &id);
				Child* child = findChildIdInGarden(city->garden[i], id);
				if(child == NULL)
				{
					if(addChild(city->garden[i], id) == 0)
					{
						printf("Child was added successfully\n");
						return;
					}
				}
				else
					printf("Child is already in %s garden.\n", city->garden[i]->name);
			}while(1);
		}
	}
	printf("No garden by this name.\n");
}

void birthdayToChild(City* city)
{
	char gardenName[GARDEN_NAME_LENGTH];
	int childId;
	Child* child = NULL;
	Kindergarden* garden = NULL;

	printf("Enter garden name: \n");
	scanf("%s", gardenName);

	garden = findGardenInCity(city, gardenName);
	if(garden != NULL)
	{
		printf("Enter child's ID: \n");
		scanf("%d", &childId);
		child = findChildIdInGarden(garden, childId);
		if(child != NULL)
			child->age += 1;
		else
			printf("No child by ID number %d\n", childId);
	}
	else
		printf("No garden by this name.\n");
}

int countChova(City* city)
{
	int i, counter = 0;
	for (i = 0; i < city->numOfGardens; i++)
		if (city->garden[i]->type == CHOVA)
			counter += city->garden[i]->numOfChildren;
	return counter;
}




