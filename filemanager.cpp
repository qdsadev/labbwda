#include "filemanager.h"


#include <QDebug>
FILE* openFile(char* fileName){
    return fopen(fileName, "r");
}

void getData(FILE* file, Data& data){
    data.countColumn = getCountColumn(file);
    data.size = getLenRegion(file, data);
    data.info = allocateMatrix(data.size, data.countColumn, STRING_SCALE);
    data.nameColumn = allocateArr(data.countColumn, STRING_SCALE);
    rewind(file);
}

void scanFile(FILE* file, Data& data){
    rewind(file);
    getData(file, data);
    char* string = allocateString(STRING_SCALE);
    char** splitstring = allocateArr(data.countColumn, STRING_SCALE);
    fgets(string, STRING_SCALE, file);
    splitString(data.nameColumn, string, data.countColumn);
    int i = 0;
    while (fgets(string, STRING_SCALE, file)){
        if (!stringCheck(string))
            continue;
        splitString(splitstring, string, data.countColumn);
        if (!strcmp(splitstring[1], data.region)){
            copyArr(data.info[i], splitstring, data.countColumn);
            i++;
        }
    }
    freeString(string);
    freeArr(splitstring, data.countColumn);
}


int getLenRegion(FILE* file, Data& data){
    rewind(file);
    char* string = allocateString(STRING_SCALE);
    char** splitstring = allocateArr(data.countColumn, STRING_SCALE);
    int count = 0;
    while (fgets(string, STRING_SCALE, file)){
        if (!stringCheck(string))
            continue;
        splitString(splitstring, string, data.countColumn);
        if (!strcmp(splitstring[1], data.region))
            count++;
    }
    freeString(string);
    freeArr(splitstring, data.countColumn);
    return count;
}


int getCountColumn(FILE* file){
    rewind(file);
    int count = 1;
    char* string = allocateString(STRING_SCALE);
    fgets(string, STRING_SCALE, file);
    for (int i = 0; string[i]; i++){
        if (string[i] == ','){
            count++;
        }
    }
    freeString(string);
    return count;
}


void retrieveData(Data& data, char* fileName, bool& flag, Errors& error){
    FILE* file = openFile(fileName);
    if(!file){
        error = File;
    } else {
        if(flag){
            freeArr(data.nameColumn, data.countColumn);
            freeMatrix(data.info, data.size, data.countColumn);
        }
        scanFile(file, data);
        flag = true;
    }
}

