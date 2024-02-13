#include "pipex.h"

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
    t_pipex p;
    char *envp[] = {
        "OTHER=other",
        "PATH=/usr/local/bin:/usr/bin:/bin",
        NULL
    };      
    p.envp = envp;

    // act
    char *result = find_path(&p);

    // assert
    TEST_ASSERT_NOT_NULL(result);
    TEST_ASSERT_EQUAL_STRING("/usr/local/bin", result);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_function_should_do_blah);
    // add more RUN_TEST lines for each test
    return UNITY_END();
}