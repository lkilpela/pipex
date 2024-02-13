#include "pipex.h"
#include <stdio.h>
#include <unistd.h> // for environ

void setUp(void)
{
    // initialize stuff before each test
}

void tearDown(void)
{
    // clean up after each test
}

/*void test_function_should_do_blah(void)
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
}*/
extern char **environ;

void test_find_path(void)
{
    // arrange
    t_pipex p;
    p.envp = environ; // use actual environment variables

    // act
    char **result = find_path(&p);

    // print PATH environment variable and result
    printf("PATH: %s\n", getenv("PATH"));
    printf("Result: %s\n", *result);

    // assert
    TEST_ASSERT_NOT_NULL(result);

    // Check that the returned path is part of the PATH environment variable
    char *path_env = getenv("PATH");
    TEST_ASSERT_NOT_NULL(path_env);
    TEST_ASSERT_NOT_NULL(strstr(path_env, *result));
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_find_path);
    // add more RUN_TEST lines for each test
    return UNITY_END();
}