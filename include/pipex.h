/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 11:49:51 by lkilpela          #+#    #+#             */
/*   Updated: 2024/03/07 22:00:58 by lkilpela         ###   ########.fr       */
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
	ERR_FORK,
	ERR_PIPE,
	ERR_DUP2,
	ERR_EXECVE,
	ERR_OPEN,
	ERR_CLOSE,
	ERR_WAITPID,
	ERR_CMD_INVALID,
	ERR_FILENAME,
	ERR_CMD_NOT_EXECUTABLE,
	ERR_FILE_OR_CMD_NOT_FOUND,
	ERR_FILE_NOT_READABLE,
	ERR_FILE_NOT_WRITABLE,
	ERR_CMD_IS_DIRECTORY,
	LAST_ERROR
};

typedef struct s_pipex
{
	char	**argv;// Command-line arguments
	int		argc;// Count of command-line arguments
	char	**envp;// Environment variables
	pid_t	pids[2];//an array of PIDs
	int		infilefd;// File descriptor for the input file
	int		outfilefd;// File descriptor for the output file
	char	**paths;// Array of paths for executable lookup
	char	*child_path;// Path for the child process or command
	char	**child_cmd;// Array of command and arguments for child process
	int		pipefd[2];// Array to hold the file descriptors for the pipe
	int		arg_index;
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
int		execute_first_command(t_pipex *p, t_tokenize *t);
int		execute_second_command(t_pipex *p, t_tokenize *t);

//parent process
int		wait_children(t_pipex *p, t_tokenize *t);

// error handler
void	error(int e);

//untils
void	cleanup(t_pipex *p);
void	free_paths(char **paths);
char	**resize_array(char **old_array, int old_count, int new_count);
#endif