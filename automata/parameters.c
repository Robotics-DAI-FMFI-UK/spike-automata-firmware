#include "parameters.h"

void *parameters[MAX_NUMBER_OF_PARAMETERS];

char *get_param_as_str(int index) {
    return (char *) (parameters[index]);
}

//void set_parameter(int index, void value){
//    parameters[index] = value;
//}