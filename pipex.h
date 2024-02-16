/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 11:49:51 by lkilpela          #+#    #+#             */
/*   Updated: 2024/02/16 13:42:31 by lkilpela         ###   ########.fr       */
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
	ERR_WRITE	
};

typedef struct s_pipex
{
	char	**argv;
	int		argc;
	char	**envp;
	pid_t	*pids;
	int		infile;
	int		outfile;
	char	**paths;
	char	*child_path;
	char    *parent_path;
	char	**child_cmd;
	char	**parent_cmd;
}				t_pipex;

typedef struct s_tokenize
{
	int		in_quotes;// a flag:current character is inside quotes. This is useful for handling quoted strings in the command line.
	int		backslash;// a flag:current character is preceded by a backslash. This is useful for handling escape sequences in the command line.
	int 	count;//a counter for the number of arguments found so far.
	char	**args;//a dynamic array that holds the arguments found so far. Each argument is a string.
}				t_tokenize;

void	init_pipex(int argc, char **argv, char **envp, t_pipex *p);
void	init_tokenize(t_tokenize *t);
void	error(t_pipex *p, int e);
void	free_paths(char **paths);
char	*find_command(t_pipex *p, char *cmd);
char	**resize_array(char **old_array, int old_count, int new_count);

#endif