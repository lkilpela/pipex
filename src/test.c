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
    int i = 0;
    char *cmds[] = {"grep Hello", "ls -l", "wc -l", "grep a1", "cat -e", "awk '{count++} END {print count}'", NULL};
    
    while (cmds[i])
    {
        init_tokenize(&t);
        char **command = split_command(&t, cmds[i]);
        if (command != NULL) 
        {
            printf("\033[1;34msplit_command result for '%s':\033[0m\n", cmds[i]);
            for (int j = 0; command[j] != NULL; j++)
                printf("%s\n", command[j]);
        }
        else 
        {
            printf("\033[1;31mError: command not found for '%s'\033[0m\n", cmds[i]);
            TEST_ASSERT_NOT_NULL(command);  // Assert that command is not NULL
        }
        i++;
    }
}

void test_setup_first_command(void)
{
    // Set up the t_pipex structure
    t_pipex p;
    p.argv = malloc(sizeof(char*) * 3);  // Allocate memory for argv
    p.argv[0] = "pipex";
    p.argv[1] = "infile.txt";
    p.argv[2] = "grep Hello";
    p.argc = 3;  // Update argc to reflect the number of arguments
    pipe(p.pipefd);

    // Run the function
    int result = setup_first_command(&p);
    TEST_ASSERT_EQUAL_INT(0, result);

    // Read and check the pipe
    char buf[50];
    read(p.pipefd[0], buf, 50);
    TEST_ASSERT_EQUAL_STRING("Hello, world!", buf);

    // Clean up
    close(p.pipefd[0]);
    close(p.pipefd[1]);
    free(p.argv);  // Free the allocated memory for argv
}


int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_paths);
    RUN_TEST(test_tokenize);
    RUN_TEST(test_setup_first_command);
    return UNITY_END();
}
