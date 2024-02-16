/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 15:40:37 by lkilpela          #+#    #+#             */
/*   Updated: 2024/02/16 15:52:06 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void    redirect_input(char *infile)
{
    int fd;

    fd = open(infile, O_RDONLY);
    if (fd == -1)
        error(ERR_OPEN);
    if (dup2(fd, STDIN_FILENO) == -1)
        error(ERR_DUP2);
    if (close(fd) == -1)
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
void   redirect_output(char *outfile)
{
    int fd;

    fd = open(outfile, O_CREAT | O_WRONLY | O_TRUNC, PERMISSIONS);
    if (fd == -1)
        error(ERR_OPEN);
    if (dup2(fd, STDOUT_FILENO) == -1)
        error(ERR_DUP2);
    if (close(fd) == -1)
        error(ERR_CLOSE);    
}

int main(int argc, char **argv, char **envp)
{
    t_pipex p;

    init(argc, argv, envp, &p);
    redirect_input(p.argv[1]);
    redirect_output(p.argv[p.argc - 1]);
    execve(p.child_path, p.argv, p.envp);
    error(ERR_EXECVE);
    return (0);
}
