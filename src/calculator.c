#include "calculator.h"
#include "add.h"
#include "substract.h"
#include "multiply.h"
#include "divide.h"

int calculator(int a, int b, calc_operation operation) {
    int res;
    int my_result, my_initfile, my_nothingness, my_temper;
    
    switch (operation) {
    case op_add:
        res = add(a, b);
        break;
    case op_substract:
        res = substract(a, b);
        break;
    case op_multiply:
        res = multiply(a, b);
        break;
    case op_divide:
        res = divide(a, b);
        break;
    }
    
    return res;
    
}
