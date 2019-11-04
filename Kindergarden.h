
#ifndef KINDERGARDEN_H_
#define KINDERGARDEN_H_

#include <stdio.h>
#include "Child.h"

#define GARDEN_NAME_LENGTH 100

typedef enum {CHOVA, TROM_CHOVA, TROM_TROM_CHOVA, numOfTypes} GardenType;
const char* typeTitles[numOfTypes];

typedef struct {
	char* name;
	GardenType type;
	Child** children;
	int numOfChildren;
}Kindergarden;

void readGardenFromFile(Kindergarden* pGarden, FILE* file);

void writeGardenToFile(Kindergarden* pGarden, FILE* file);

void printGarden(const Kindergarden* pGarden);

void releaseGarden(Kindergarden* pGarden);

void initGarden(Kindergarden* kindergarden, char* name);

int addChild(Kindergarden* kindergarden, int id);

Child* findChildIdInGarden(const Kindergarden* kindergarden, int id);

#endif /* KINDERGARDEN_H_ */
