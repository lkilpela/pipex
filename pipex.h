/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 11:49:51 by lkilpela          #+#    #+#             */
/*   Updated: 2024/02/13 12:06:43 by lkilpela         ###   ########.fr       */
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
# include "../lib/libft/include/libft.h"

typedef struct s_pipex
{
    int     argc;
    char    **argv;
    char    **envp;
    pid_t   *pids;
    int     infile;
    int     outfile;
    char    **paths;
    char    **cmd;
}              t_pipex;

#endif