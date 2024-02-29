/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 11:49:51 by lkilpela          #+#    #+#             */
/*   Updated: 2024/02/29 14:08:13 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "lib/libft/include/libft.h"

# include <fcntl.h> //open
//close, read, write, access, dup, dup2, execve, fork, pipe, unlink
# include <unistd.h>  
# include <stdlib.h> //malloc, free, exit
# include <stdio.h> // perror
# include <string.h> //strerror
# include <sys/wait.h> // wait, waitpid

# define MAX_TOKENS	100
# define PERMISSIONS	0644

enum	e_pipe
{
	RD_END,
	WR_END
};

enum	e_error
{
	ERR_NONE,
	ERR_SYNTAX,
	ERR_MEM,
	ERR_FORK,
	ERR_PIPE,
	ERR_DUP2,
	ERR_EXECVE,
	ERR_MALLOC,
	ERR_OPEN,
	ERR_CLOSE,
	ERR_READ,
	ERR_WRITE,
	ERR_WAITPID,
	ERR_CMD_INVALID,
	ERR_FILENAME,
	ERR_CMD_NOT_FOUND
	LAST_ERROR
};

typedef struct s_pipex
{
	char	**argv;         // Command-line arguments
	int		argc;           // Count of command-line arguments
	char	**envp;         // Environment variables
	pid_t	pid;          // Single process IDs
	int		infilefd;      // File descriptor for the input file
	int		outfilefd;     // File descriptor for the output file
	char	**paths;        // Array of paths for executable lookup
	char	*child_path;    // Path for the child process or command
	char    *parent_path;   // Path for the parent process or command
	char	**child_cmd;    // Array of command and arguments for child process
	char	**parent_cmd;   // Array of command and arguments for parent process
	int		pipefd[2];		// Array to hold the file descriptors for the pipe
}				t_pipex;

typedef struct s_tokenize
{
	int		in_quotes;// a flag:current character is inside quotes. This is useful for handling quoted strings in the command line.
	//int		backslash;// a flag:current character is preceded by a backslash. This is useful for handling escape sequences in the command line.
	int 	count;//a counter for the number of arguments found so far.
	char	**args;//a dynamic array that holds the arguments found so far. Each argument is a string.
}				t_tokenize;

// Retrieves the environment paths for Unix commands
char	**get_envpaths(t_pipex *p);

// Finds the full path of an executable command
char	*find_executsble(t_pipex *p, char *cmd);

// Initializes the pipex structure with command line arguments and environment variables
void	init_pipex(int argc, char **argv, char **envp, t_pipex *p);

// Initializes the tokenize structure
void	init_tokenize(t_tokenize *t);

// Handles errors based on the error code 'e'
void	error(int e);

// Frees the memory allocated for the paths
void	free_paths(char **paths);

// Finds the full path of a command
char	*find_command(t_pipex *p, char *cmd);

// Resizes an array to accommodate new elements
char	**resize_array(char **old_array, int old_count, int new_count);

// Initializes the tokenize structure
void	init_tokenize(t_tokenize *t);

// Toggles the 'in_quotes' field of the tokenize structure based on the character 'c'
void	toggle_quotes(t_tokenize *t, char c);

// Adds a word to the 'args' field of the tokenize structure
int	add_word(t_tokenize *t, char *start, char *end);

// Splits a command string into words based on spaces
void	split_on_space(t_tokenize *t, char *cmd);

// Splits a command string into words and stores them in the 'args' field of the tokenize structure
char	**split_command(t_tokenize *t, char *cmd);

void    setup_first_command(t_pipex *p);
void   setup_second_command(t_pipex *p);
void	execute_child(t_pipex *p, t_tokenize *t, char *cmd);
void    execute_first_command(t_pipex *p, t_tokenize *t, char *cmd);
void 	execute_second_command(t_pipex *p, t_tokenize *t, char *cmd);


#endif