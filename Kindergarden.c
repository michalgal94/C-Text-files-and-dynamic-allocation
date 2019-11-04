
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "Kindergarden.h"
#include "func.h"

const char* typeTitles[numOfTypes] = {"Chova", "Trom Chova", "Trom Trom Chova"};

void readGardenFromFile(Kindergarden* pGarden, FILE* file)
{
	int typeIndex, i;
	// check size needed to be allocated to garden's name.
	char tempStr[GARDEN_NAME_LENGTH];
	fscanf(file, "%s", tempStr);
	int nameSize = strlen(tempStr);
	pGarden->name = (char*)malloc(nameSize*sizeof(char));
	fseek(file, -nameSize-1 , SEEK_CUR);
	//reading garden's details
	fscanf(file, "%s %d %d", pGarden->name, &typeIndex, &pGarden->numOfChildren);
	pGarden->type = typeIndex;

	pGarden->children = (Child**)malloc((pGarden->numOfChildren)*sizeof(Child*));
	if(!pGarden->children)
		return;
	for(i = 0; i < pGarden->numOfChildren; i++)
	{
		pGarden->children[i] = (Child*)malloc(1*sizeof(Child));
		if(!pGarden->children[i])
			return;
		readChildFromFile(pGarden->children[i], file);
	}
}

void writeGardenToFile(Kindergarden* pGarden, FILE* file)
{
	int i;
	fprintf(file,"%s  %d %d\n", pGarden->name ,pGarden->type,pGarden->numOfChildren);
	for(i =0; i < pGarden->numOfChildren; i++)
		writeChildToFile(pGarden->children[i], file);
}

void printGarden(const Kindergarden* pGarden)
{
	int i;
	printf("Name: %s \tType: %s \t%d children: \n", pGarden->name, typeTitles[pGarden->type], pGarden->numOfChildren);
	for(i = 0; i < pGarden->numOfChildren; i++)
		printChild(pGarden->children[i]);
}

void releaseGarden(Kindergarden* pGarden)
{
	int i;
	for (i = 0; i < pGarden->numOfChildren; i++)
		releaseChild(pGarden->children[i]);
	free(pGarden->children);
	free(pGarden->name);
}

void initGarden(Kindergarden* kindergarden, char* name)
{
	int i, id, howMany, isAdded, size = strlen(name);
	kindergarden->name = (char*)malloc(size*sizeof(char));
	strcpy(kindergarden->name, name);

	printf("Garden's type: \nEnter 0 for Chova. \nEnter 1 for Trom Chova. \nEnter 2 for Trom Trom Chova\n");
	scanf("%d", (int*)&kindergarden->type);

	kindergarden->numOfChildren = 0;
	printf("How many children?\n");
	scanf("%d", &howMany);
	kindergarden->children = (Child**)malloc(kindergarden->numOfChildren*sizeof(Child*));
	for(i = 0; i < howMany; i++)
	{
		printf("Enter child number %d ID:\n", (i+1));
		scanf("%d", &id);
		isAdded = addChild(kindergarden, id);
		if(isAdded == 0)
			printf("Child added successfully\n");
		else if(isAdded == -2)
		{
			printf("Child is already in garden.\n");
			i--;
		}
	}
}

int addChild(Kindergarden* kindergarden, int id)
{
	int i;
	kindergarden->children = (Child**)realloc(kindergarden->children, sizeof(Child*)*(kindergarden->numOfChildren) + 1);
	if (kindergarden->children == NULL)
		return -1;

	kindergarden->children[kindergarden->numOfChildren] = (Child*)malloc(1*sizeof(Child));
	if (kindergarden->children[kindergarden->numOfChildren] == NULL)
		return -1;

	for(i = 0; i < kindergarden->numOfChildren; i++)
		if(kindergarden->children[i]->id == id)
			return -2;

	initChild(kindergarden->children[kindergarden->numOfChildren], id);
	kindergarden->numOfChildren++;
	return 0;
}

Child* findChildIdInGarden(const Kindergarden* kindergarden, int id)
{
	int i;
	for (i=0; i<kindergarden->numOfChildren; i++)
		if(kindergarden->children[i]->id == id)
			return kindergarden->children[i];
	return NULL;
}
