#include "stringworks.h"


void splitString(char** newString, char* string, int count){
    char* time;
    time = strtok(string, ",");
    for (int i = 0; i < count; i++){
        strcpy(newString[i], time);
        time = strtok(NULL, ",");
    }
}


void copyArr(char** newArr, char** arr, int count){
    for (int i = 0; i < count ; i++){
        strcpy(newArr[i], arr[i]);
    }
}


bool stringCheck(char* line){
    bool flag = true;
    for (int i = 1; line[i]; i++){
        if (line[i] == line[i-1] && line[i] == ','){
            flag = false;
            break;
        }
    }
    return flag;
}
