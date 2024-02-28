/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 15:40:37 by lkilpela          #+#    #+#             */
/*   Updated: 2024/02/28 21:42:30 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//first child process write its output to the pipe
void    redirect_output(t_pipex *p)
{
    p->infilefd = open(p->argv[1], O_RDONLY);
    if (p->infilefd == -1)
		error(ERR_OPEN);
    if (dup2(p->pipefd[1], STDOUT_FILENO) == -1)
        error(ERR_DUP2);
    if (close(p->pipefd[1]) == -1)
        error(ERR_CLOSE);    
}

void    execute_first_command(char *cmd, t_pipex *p, t_tokenize *t)
{
    int     status;
    
    p->pids = fork();
    if (p->pids == -1)
        error(ERR_FORK);
    if (p->pids == 0)
    {
        redirect_output(p);
        if (execve(cmd, t->args[2], NULL) == -1)
            error(ERR_EXECVE);
    }
    else
    {
        if (waitpid(p->pids, &status, 0) == -1)
            error(ERR_WAITPID);
    }
}
// second child process read its input from the pipe
void   redirect_input(t_pipex *p)
{
    p->outfilefd = open(p->argv[p->argc - 1],
				O_CREAT | O_WRONLY | O_TRUNC, PERMISSIONS);
	if (p->outfilefd == -1)
		error(ERR_OPEN);
    if (dup2(p->pipefd[0], STDIN_FILENO) == -1)
        error(ERR_DUP2);
    if (close(p->pipefd[0]) == -1)
        error(ERR_CLOSE);    
}

void execute_second_command(char *cmd, t_pipex *p, t_tokenize *t)
{
    int     status;
    
    p->pids = fork();
    if (p->pids == -1)
        error(ERR_FORK);
    if (p->pids == 0)
    {
        redirect_input(p);
        if (execve(cmd, t->args[3], NULL) == -1)
            error(ERR_EXECVE);
    }
    else
    {
        if (waitpid(t->pids, &status, 0) == -1)
            error(ERR_WAITPID);
    }
}

