#include "multiply.h"
#include "unity.h"

void test_multiply_by_zero() {
    TEST_ASSERT_EQUAL(0, multiply(0, 6));
}

void test_multiply_by_one() {
    TEST_ASSERT_EQUAL(6, multiply(1, 6));
}


