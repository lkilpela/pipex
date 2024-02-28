/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 15:40:37 by lkilpela          #+#    #+#             */
/*   Updated: 2024/02/28 21:29:32 by lkilpela         ###   ########.fr       */
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

void    execute_first_command(char *cmd, t_pipex *p)
{
    int status;
    
    t->pids = fork();
    if (t->pids == -1)
        error(ERR_FORK);
    redirect_output(p);
    if (t->pids == 0)
    {
        if (execve(cmd, p->argv, NULL) == -1)
            error(ERR_EXECVE);
    }
    else
    {
        if (waitpid(t->pids, &status, 0) == -1)
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

void execute_second_command(char *cmd, char **args, int pipefd[2])
{
    // Fork a new process
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // This is the child process. Redirect its standard input to the pipe.
        if (dup2(pipefd[0], STDIN_FILENO) == -1) {
            perror("dup2");
            exit(EXIT_FAILURE);
        }

        // Execute the command.
        if (execve(cmd, args, NULL) == -1) {
            perror("execve");
            exit(EXIT_FAILURE);
        }
    } else {
        // This is the parent process. Wait for the child to finish.
        int status;
        if (waitpid(pid, &status, 0) == -1) {
            perror("waitpid");
            exit(EXIT_FAILURE);
        }
    }
}

