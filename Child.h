

#ifndef CHILD_H_
#define CHILD_H_

typedef struct {
	int id;
	int age;
}Child;

void readChildFromFile(Child* pChild, FILE* file);

void writeChildToFile(Child* pChild, FILE* file);

void printChild(const Child* pChild);

void releaseChild(Child* pChild);

void initChild(Child* child, int id);

#endif /* CHILD_H_ */
