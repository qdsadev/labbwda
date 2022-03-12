#ifndef ENTRYPOINT_H
#define ENTRYPOINT_H

#include "appcontext.h"
#include "logic.h"
#include "filemanager.h"

enum Operation {
    LoadData,
    Calculate
};

enum Errors {
    Success,
    Read,
    ColumnNum,
    Region,
    File
};

void doOperation(Operation operation, Data& data, int column, bool& flag, Errors& error);
void retrieveData(Data& data, char* fileName, bool& flag, Errors& error);
#endif // ENTRYPOINT_H
