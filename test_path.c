#include "pipex.h"
#include <stddef.h> // Include the header file that defines NULL
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h> 
#include <unistd.h> // for environ
#include "unity/src/unity.h" // Test framework


void setUp(void) {
    // Put setup code here
}

void tearDown(void) {
    // Put teardown code here
}

extern char **environ;

void test_paths(void)
{
    // arrange
    t_pipex p;
    p.envp = environ; // use actual environment variables
    char *cmd[] = {"ls", 0};

   // Test get_envpaths
    char **envpaths_result = get_envpaths(&p);
    while (*envpaths_result != 0) {
        printf("\033[1;32mget_envpaths result: %s\033[0m\n", *envpaths_result);
        envpaths_result++;
    }    
    TEST_ASSERT_NOT_NULL(envpaths_result);

    // Test find_command
    p.cmd = cmd;
    char *command = find_command(&p);
    char *executable_result;
    printf("\033[1;32mfind_command result: %s\033[0m\n", command);
    if (command == 0) {
        TEST_ASSERT_NULL(command);
        printf("\033[1;31mError: find_command returned NULL\033[0m\n");
    } else if (strchr(command, '/') != 0) {
        TEST_ASSERT_NOT_NULL(command);
    } else {
        char *full_path = find_executable(&p);
        printf("\033[1;32mfind_executable result: %s\033[0m\n", full_path);
        TEST_ASSERT_NOT_NULL(full_path);
    }

    // Free allocated memory
    free(command);
    free_paths(p.paths);

}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_paths);
    return UNITY_END();
}
