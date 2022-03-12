#ifndef APPCONTEXT_H
#define APPCONTEXT_H

struct Data {
    char* name;
    char** nameColumn;
    char*** info;
    int countColumn;
    int size;
    char* region;
    bool fileExists;
    double min;
    double max;
    double intermediate;
};


#endif // APPCONTEXT_H
