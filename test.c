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
    
   // Test get_envpaths
    char **envpaths_result = get_envpaths(&p);
    while (*envpaths_result != 0) {
        printf("\033[1;32mget_envpaths result: %s\033[0m\n", *envpaths_result);
        envpaths_result++;
    }
    //Assert    
    TEST_ASSERT_NOT_NULL(envpaths_result);

    // arrange
    char *cmds[] = {"grep", "awk", "ls", "cat", "/usr/local/bin/grep", NULL};
    int i = 0;
    p.paths = get_envpaths(&p);

    //Act: find_command for each command
    while (cmds[i])
    {
        char *full_path = find_command(&p, cmds[i]);
        
        if (full_path != NULL) 
            printf("\033[1;34mfind_command result for '%s': %s\033[0m\n", cmds[i], full_path);
        else 
        {
            printf("\033[1;31mError: command not found for '%s'\033[0m\n", cmds[i]);
            TEST_ASSERT_NOT_NULL(full_path);
        }
        i++;
    }
}

void test_tokenize(void) 
{
    t_tokenize t;
    char *cmds[] = {"grep Hello", "ls -l", "wc -l", "grep a1", "cat -e", "awk '{count++} END {print count}'", NULL}
    
    // Test with "grep Hello"
    init_tokenize(&t);
    split_command(&t, "grep Hello");
    TEST_ASSERT_EQUAL_STRING("grep", t.args[0]);
    TEST_ASSERT_EQUAL_STRING("Hello", t.args[1]);
    TEST_ASSERT_NULL(t.args[2]);

}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_paths);
    RUN_TEST(test_tokenize);
    return UNITY_END();
}
