/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 11:49:51 by lkilpela          #+#    #+#             */
/*   Updated: 2024/02/13 21:36:36 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h> //open
//close, read, write, access, dup, dup2, execve, fork, pipe, unlink
# include <unistd.h>  
# include <stdlib.h> //malloc, free, exit
# include <stdio.h> // perror
# include <string.h> //strerror
# include <sys/wait.h> // wait, waitpid
# include "lib/libft/include/libft.h"
# include "test/unity/src/unity.h" // Test framework

typedef enum e_error
{
	NO_ERROR,
	ERR_FORK,
	ERR_PIPE,
	ERR_DUP2,
	ERR_EXECVE,
	ERR_MALLOC,
	ERR_OPEN,
	ERR_CLOSE,
	ERR_READ,
	ERR_WRITE
}			t_error;

typedef struct s_pipex
{
	char	**envp;
	pid_t	*pids;
	int		infile;
	int		outfile;
	char	**paths;
	char	**cmd1;
	char	**cmd2;
}				t_pipex;

char	**find_path(t_pipex *p);

#endif