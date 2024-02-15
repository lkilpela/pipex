/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 11:49:51 by lkilpela          #+#    #+#             */
/*   Updated: 2024/02/15 13:48:48 by lkilpela         ###   ########.fr       */
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

void	free_paths(char **paths);
char	*find_command(t_pipex *p, char *cmd)

#endif