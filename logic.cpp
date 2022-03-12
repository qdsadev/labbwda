#include "logic.h"


void obtainDigits(Data& data, int column){
    double* arrDigits = (double*)calloc(data.size, sizeof(double));
    for (int i = 0; i < data.size; i++){
        arrDigits[i] = atof(data.info[i][column]);
    }
    midNumber(arrDigits, data.size, data);
    maxNumber(arrDigits, data.size, data);
    minNumber(arrDigits, data.size, data);
    free(arrDigits);
}


void midNumber(double* arrDigits, int size, Data& data){
    double sum = 0;
    for(int i = 0; i<size; i++){
        sum += *(arrDigits+i);
    }
    data.intermediate = sum/size;
}


void maxNumber(double* arrDigits, int size, Data& data){
    double max = *arrDigits;
    for(int i = 0; i<size; i++){
        if(max<*(arrDigits+i)){
            max=*(arrDigits+i);
        }
    }
    data.max = max;
}


void minNumber(double* arrDigits, int size, Data& data){
    double min = *arrDigits;
    for(int i = 0; i<size; i++){
        if(min>*(arrDigits+i)){
            min=*(arrDigits+i);
        }
    }
    data.min = min;
}

