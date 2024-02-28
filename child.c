/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 15:40:37 by lkilpela          #+#    #+#             */
/*   Updated: 2024/02/28 13:42:38 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void    redirect_input(t_pipex *p)
{
    p->infile = open(p->argv[1], O_RDONLY);
    if (p->infile == -1)
		error(ERR_OPEN);
    if (dup2(p->infile_fd , STDIN_FILENO) == -1)
        error(ERR_DUP2);
    if (close(p->infile_fd) == -1)
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

void    setup_pipe(int pipefd[2])
{
    if (pipe(pipefd) == -1)
        error(ERR_PIPE);
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

void   redirect_output(t_pipex *p)
{
    p->outfile = open(p->argv[p->argc - 1],
				O_CREAT | O_WRONLY | O_TRUNC, PERMISSIONS);
	if (p->outfile == -1)
		error(ERR_OPEN);
    if (dup2(fd, STDOUT_FILENO) == -1)
        error(ERR_DUP2);
    if (close(fd) == -1)
        error(ERR_CLOSE);    
}

void cleanup(int pipefd[2], pid_t pid1, pid_t pid2)
{
    // Close the pipe file descriptors
    if (close(pipefd[0]) == -1) {
        error(ERR_CLOSE);
    }
    if (close(pipefd[1]) == -1) {
        error(ERR_CLOSE);
    }

    // Wait for the child processes to finish
    int status;
    if (waitpid(pid1, &status, 0) == -1) {
        perror("waitpid");
        exit(EXIT_FAILURE);
    }
    if (waitpid(pid2, &status, 0) == -1) {
        perror("waitpid");
        exit(EXIT_FAILURE);
    }
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
