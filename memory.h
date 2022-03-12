#ifndef MEMORY_H
#define MEMORY_H

#include <stdlib.h>


char* allocateString(int size);
char** allocateArr(int count, int size);
char*** allocateMatrix(int len, int count, int size);

void freeString(char* string);
void freeArr(char** mas, int count);
void freeMatrix(char*** matrix, int len, int count);


#endif // MEMORY_H
