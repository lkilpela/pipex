/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 11:49:51 by lkilpela          #+#    #+#             */
/*   Updated: 2024/04/04 10:02:41 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../lib/libft/include/libft.h"

# include <fcntl.h> //open
//close, read, write, access, dup, dup2, execve, fork, pipe, unlink
# include <unistd.h>  
# include <stdlib.h> //malloc, free, exit
# include <stdio.h> // perror
# include <string.h> //strerror
# include <sys/wait.h> // wait, waitpid

# define MAX_TOKENS	100
# define PERMISSIONS	0644

enum	e_error
{
	ERR_NONE,
	ERR_SYNTAX,
	ERR_FILE,
	ERR_CMD,
	ERR_DIR,
	ERR_PERM,
	ERR_FORK,
	ERR_PIPE,
	ERR_DUP2,
	ERR_EXECVE,
	ERR_OPEN,
	ERR_CLOSE,
	ERR_WAITPID,
	LAST_ERROR
};

enum	exit_code
{
	SUCCESS = 0,
	GENERAL_ERROR = 1,
	
	INPUT_FILE_NOT_FOUND,
	OUTPUT_FILE_NOT_FOUND,
	
	PIPE_FAILURE,
	FORK_FAILURE,
	COMMAND_EXECUTION_FAILURE = 126,
	COMMAND_NOT_FOUND = 127,
	INVALID_ARGUMENTS = 128,
};


typedef struct s_command
{
	char	*path;
	char	**args;
}				t_command;

typedef struct s_pipex
{
	char		**argv;// Command-line arguments
	int			argc;// Count of command-line arguments
	char		**envp;// Environment variables
	pid_t		pids[2];//an array of PIDs
	int			infilefd;// File descriptor for the input file
	int			outfilefd;// File descriptor for the output file
	char		**paths;// Array of paths for executable lookup
	int			pipefd[2];// Array to hold the file descriptors for the pipe
	int			arg_index;
	t_command	cmds[2];
}				t_pipex;

typedef struct s_tokenize
{
	int		in_quotes;//flag quoted string:current character is inside quotes.
	int		count;//a counter for the number of arguments found so far.
	char	**args;//a dynamic array that holds string arguments found so far.
}				t_tokenize;

// init
void	init_pipex(int argc, char **argv, char **envp, t_pipex *p);
void	init_tokenize(t_tokenize *t);

// path handler
char	*find_command(t_pipex *p, char *cmd);

// command handler
char	**split_command(t_tokenize *t, char *cmd);

//child process
int		execute_first_command(t_pipex *p);
int		execute_second_command(t_pipex *p);

//parent process
int		wait_children(t_pipex *p);

// error handler
void	error(int e);

//untils
void	cleanup(t_pipex *p);
void	free_paths(char **paths);
char	**resize_array(char **old_array, int old_count, int new_count);
#endif