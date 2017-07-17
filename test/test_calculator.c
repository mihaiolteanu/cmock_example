#include "unity.h"
#include "calculator.h"
#include "mock_add.h"
#include "mock_substract.h"
#include "mock_multiply.h"
#include "mock_divide.h"

void test_calculator_add() {
    add_ExpectAndReturn(2, 8, 10);
    
    TEST_ASSERT_EQUAL(10, calculator(2, 8, op_add));
}

void test_calculator_substract() {
    substract_ExpectAndReturn(10, 4, 6);
    
    TEST_ASSERT_EQUAL(6, calculator(10, 4, op_substract));
}

void test_calculator_multiply() {
    multiply_ExpectAndReturn(2, 5, 10);
    
    TEST_ASSERT_EQUAL(10, calculator(2, 5, op_multiply));
}

void test_calculator_divide() {
    divide_ExpectAndReturn(10, 5, 2);
    
    TEST_ASSERT_EQUAL(2, calculator(10, 5, op_divide));
}
