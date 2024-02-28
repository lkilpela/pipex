/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 15:40:37 by lkilpela          #+#    #+#             */
/*   Updated: 2024/02/28 20:51:37 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void    redirect_input(t_pipex *p)
{
    p->infilefd = open(p->argv[1], O_RDONLY);
    if (p->infilefd == -1)
		error(ERR_OPEN);
    if (dup2(p->pipefd[1], STDOUT_FILENO) == -1)
        error(ERR_DUP2);
    if (close(p->pipefd[1]) == -1)
        error(ERR_CLOSE);    
}

void    execute_first_command(char *cmd, t_pipex *p)
{
    int status;
    
    t->pid = fork();
    if (t->pid == -1)
        error(ERR_FORK);
    if (t->pid == 0)
    {
        if (execve(cmd, p->args, NULL) == -1)
            error(ERR_EXECVE);
    }
    else
    {
        if (waitpid(t->pid, &status, 0) == -1)
            error(ERR_WAITPID);
    }
}
