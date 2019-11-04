
#include <stdio.h>
#include <stdlib.h>
#include "Child.h"

void readChildFromFile(Child* pChild, FILE* file)
{
	fscanf(file, "%d %d\n", &pChild ->id, &pChild ->age);
}

void writeChildToFile(Child* pChild, FILE* file)
{
	fprintf(file,"%d %d\n", pChild->id, pChild->age);
}

void printChild(const Child* pChild)
{
	printf("ID: %d,  Age: %d years\n", pChild ->id, pChild ->age);
}

void releaseChild(Child* pChild)
{
	free(pChild);
}

void initChild(Child* child, int id)
{
	child->id = id;

	printf("Enter child's age: ");
	scanf("%d",&child->age);
}
