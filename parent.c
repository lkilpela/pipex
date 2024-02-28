/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:41:17 by lkilpela          #+#    #+#             */
/*   Updated: 2024/02/28 15:05:30 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
    p->outfile_fd = open(p->argv[p->argc - 1],
				O_CREAT | O_WRONLY | O_TRUNC, PERMISSIONS);
	if (p->outfile_fd == -1)
		error(ERR_OPEN);
    if (dup2(p->outfile_fd, STDOUT_FILENO) == -1)
        error(ERR_DUP2);
    if (close(p->outfile_fd) == -1)
        error(ERR_CLOSE);    
}