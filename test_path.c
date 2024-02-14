#include "pipex.h"
#include <stddef.h>
#include <stdio.h>
#include <unistd.h> // for environ
#include "test/unity/src/unity.h" // Test framework

void setUp(void)
{
    // initialize stuff before each test
}

void tearDown(void)
{
    // clean up after each test
}

extern char **environ;

void test_get_envpaths(void)
{
    // arrange
    t_pipex p;
    p.envp = environ; // use actual environment variables
    
    // Check that the returned path is part of the PATH environment variable
    char *path_env = getenv("PATH");

    // act
    char **result = get_envpaths(&p);
    TEST_ASSERT_NOT_NULL(result);
    char **path = result;
    while (*path != NULL)
    {
        // print PATH environment variable and result
        printf("PATH: %s\n", getenv("PATH"));
        printf("Result: %s\n", *result);
        // Check that each path is in the PATH environment variable        
        TEST_ASSERT_NOT_NULL(strstr(path_env, *path));
        path++;
        
    }
    free_paths(result); // Assuming free_paths frees the result correctly
}
void test_find_command(void) {
    t_pipex p;
    // Assuming paths and cmd are set correctly
    p.paths = get_envpaths(&p);
    TEST_ASSERT_NOT_NULL(p.paths);
    p.cmd = "grep";
    char *result = find_command(&p);
    TEST_ASSERT_NOT_NULL(result);
    // Add more assertions to check the contents of result
    free(result);
    free_paths(p.paths);
}

void test_find_executable(void) {
    t_pipex p;
    // Assuming cmd is set correctly
    p.cmd = "grep";
    p.paths = get_envpaths(&p);
    TEST_ASSERT_NOT_NULL(p.paths);
    char *result = find_executable(&p);
    TEST_ASSERT_NOT_NULL(result);
    // Add more assertions to check the contents of result
    free(result);
    free_paths(p.paths);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_get_envpaths);
    RUN_TEST(test_find_command);
    RUN_TEST(test_find_executable);
    return UNITY_END();
}