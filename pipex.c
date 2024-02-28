/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 11:49:47 by lkilpela          #+#    #+#             */
/*   Updated: 2024/02/28 20:48:37 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	handle_syntax(t_pipex *p)
{
	if (p->argc != 5)
		error(ERR_SYNTAX);
	return (0);
}

void    setup_pipe(t_pipex *p)
{
    if (pipe(p->pipefd) == -1)
        error(ERR_PIPE);
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
	handle_syntax(&p);
    setup_pipe(&p);
    redirect_input(p.argv[1]);
    redirect_output(p.argv[p.argc - 1]);
    execve(p.child_path, p.argv, p.envp);
    error(ERR_EXECVE);
    return (0);
}
