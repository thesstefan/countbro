#include <stdio.h>

#include "errors.h"

void evaluate(int status) {
    if (status == SUCCESS)
        printf("Success\n");
    else
        printf("Fail\n");
}
