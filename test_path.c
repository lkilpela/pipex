#include "pipex.h"
#include "unity.h"

void setUp(void)
{
    // initialize stuff before each test
}

void tearDown(void)
{
    // clean up after each test
}

void test_function_should_do_blah(void)
{
    // arrange
    int expected = 42;
    
    // act
    int actual = my_function(); // replace with your function
    
    // assert
    TEST_ASSERT_EQUAL_INT(expected, actual);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_function_should_do_blah);
    // add more RUN_TEST lines for each test
    return UNITY_END();
}