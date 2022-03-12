#include "entrypoint.h"

void doOperation(Operation operation, Data& data, int column, bool& flag, Errors& error){
    switch(operation){
    case LoadData:
        retrieveData(data, data.name, flag, error);
        break;
    case Calculate:
        obtainDigits(data, column);
        break;
    }
}
