#include <stdio.h>

#include "unity.h"

void setUp()
{
}

void tearDown()
{
}

int foo()
{
    return 42;
}

int bar()
{
    return 123;
}

void test_foo()
{
    TEST_ASSERT_EQUAL(43,foo());
    TEST_ASSERT_NOT_EQUAL(123,foo());
}

void test_bar()
{
    TEST_ASSERT_EQUAL(123,bar());
    TEST_ASSERT_NOT_EQUAL(42,bar());
}

int main()
{
    UNITY_BEGIN();
    RUN_TEST(test_foo);
    RUN_TEST(test_bar);
    return UNITY_END();
}
