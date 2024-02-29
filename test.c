#include "pipex.h"
#include <stddef.h> // Include the header file that defines NULL
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h> 
#include <unistd.h> // for environ
#include "unity/src/unity.h" // Test framework

// ./pipex infile "grep Hello" "awk '{count++} END {print count}'" outfile

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
    char *cmds[] = {"grep", 0};

   // Test get_envpaths
    char **envpaths_result = get_envpaths(&p);
    while (*envpaths_result != 0) {
        printf("\033[1;32mget_envpaths result: %s\033[0m\n", *envpaths_result);
        envpaths_result++;
    }    
    TEST_ASSERT_NOT_NULL(envpaths_result);

    // Test find_command for each command
    int i = 0;
    while (cmds[i])
    {
        char *command = find_command(&p, cmds[i]);
        char *executable_result;
        printf("\033[1;34mfind_command result for '%s': %s\033[0m\n", cmds[i], command);
        if (command == 0) {
            printf("\033[1;31mError: find_command returned NULL for '%s'\033[0m\n", cmds[i]);
        } else if (strchr(command, '/') != 0) {
            TEST_ASSERT_NOT_NULL(command);
        } else {
            char *full_path = find_executable(&p, cmds[i]);
            printf("\033[1;32mfind_executable result: %s %s\033[0m\n", cmds[i], full_path);
            TEST_ASSERT_NOT_NULL(full_path);
        }
        free(command);
        i++;
    }
    // Free allocated memory
    free_paths(p.paths);

}

void test_tokenize(void) 
{
    t_tokenize t;

    // Test with "grep Hello"
    init_tokenize(&t);
    split_command(&t, "grep Hello");
    TEST_ASSERT_EQUAL_STRING("grep", t.args[0]);
    TEST_ASSERT_EQUAL_STRING("Hello", t.args[1]);
    TEST_ASSERT_NULL(t.args[2]);

    // Reset the tokenizer for the next test
    init_tokenize(&t);

    // Test with "awk '{count++} END {print count}'"
    split_command(&t, "awk '{count++} END {print count}'");
    TEST_ASSERT_EQUAL_STRING("awk", t.args[0]);
    TEST_ASSERT_EQUAL_STRING("'{count++} END {print count}'", t.args[1]);
    TEST_ASSERT_NULL(t.args[2]);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_paths);
    RUN_TEST(test_tokenize);
    return UNITY_END();
}
