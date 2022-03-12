#ifndef MANAGEFILE_H
#define MANAGEFILE_H

#include <stdio.h>
#include "memory.h"
#include <string.h>
#include "stringworks.h"
#include "appcontext.h"
#include "entrypoint.h"

#define STRING_SCALE 150



FILE* openFile(char* fileName);
void scanFile(FILE* file, Data& data);
int getCountColumn(FILE* file);
int getLenRegion(FILE* file, Data& data);


#endif // MANAGEFILE_H
