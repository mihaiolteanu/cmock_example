typedef enum {
    op_add,
    op_substract,
    op_multiply,
    op_divide
} calc_operation;

extern int calculator(int a, int b, calc_operation op);
