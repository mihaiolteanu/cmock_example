#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "calculator.h"

int main(int argc, char **argv) {
    int a, b, result;
    calc_operation operation;
    char *op;

    if (argc != 4) {
        printf("Usage: calculator a b operation\n");
        return 1;
    }

    a = atoi(argv[1]);
    b = atoi(argv[2]);
    op = argv[3];

    if ((strcmp(op, "+") == 0))
        operation = op_add;
    else if ((strcmp(op, "-") == 0))
        operation = op_substract;
    else if ((strcmp(op, "*") == 0))
        operation = op_multiply;
    else if ((strcmp(op, "/") == 0))
        operation = op_divide;
    else {
        printf("Usage: calculator a b operation\n");
        return 1;
    }
    
    result = calculator(a, b, operation);

    printf("Result: %d\n", result);

    return 0;
}
