/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 15:40:37 by lkilpela          #+#    #+#             */
/*   Updated: 2024/03/07 15:30:11 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//1st child: any reads from STDIN: read from the input file, 
//any writes to STDOUT: write to the pipe.
static int	setup_first_command(t_pipex *p)
{
	int	ret;

	p->infilefd = open(p->argv[1], O_RDONLY);
	if (p->infilefd == -1)
		error(ERR_OPEN, &p);
	ret = dup2(p->infilefd, STDIN_FILENO);
	if (ret == -1)
	{
		close(p->infilefd);
		error(ERR_DUP2, &p);
	}
	ret = dup2(p->pipefd[1], STDOUT_FILENO);
	if (ret == -1)
	{
		close(p->pipefd[1]);
		close(p->infilefd);
		error(ERR_DUP2, &p);
	}
	return (0);
}

//2nd child: any reads from STDIN: read from the pipe, 
//any writes to STDOUT: write to the output file.
static int	setup_second_command(t_pipex *p)
{
	p->outfilefd = open(p->argv[p->argc - 1],
			O_CREAT | O_WRONLY | O_TRUNC, PERMISSIONS);
	if (p->outfilefd == -1)
		error(ERR_OPEN, &p);
	if (dup2(p->pipefd[0], STDIN_FILENO) == -1)
	{
		close(p->pipefd[0]);
		error(ERR_DUP2, &p);
	}
	if (dup2(p->outfilefd, STDOUT_FILENO) == -1)
	{
		close(p->pipefd[0]);
		close(p->outfilefd);
		error(ERR_DUP2, &p);
	}
	return (0);
}

static int	execute_command( t_pipex *p, t_tokenize *t, char *cmd)
{
	p->child_cmd = split_command(t, cmd);
	if (p->child_cmd == NULL || p->child_cmd[0] == NULL)
		error(ERR_CMD_NOT_FOUND, &p);
	p->child_path = find_command(p, p->child_cmd[0]);
	if (!p->child_path)
	{
		free_paths(p->child_cmd);
		error(ERR_CMD_NOT_FOUND, &p);
	}
	if (execve(p->child_path, p->child_cmd, p->envp) == -1)
	{
		error(ERR_EXECVE, &p);
		return (-1);
	}
	return (0);
}

int	execute_first_command(t_pipex *p, t_tokenize *t)
{
	int	status;

	p->pids[0] = fork();
	if (p->pids[0] == -1)
		error(ERR_FORK, &p);
	else if (p->pids[0] == 0)
	{
		status = setup_first_command(p);
		if (status != 0)
			exit(status);
		status = execute_command(p, t, p->argv[2]);
		if (status != 0)
			exit(status);
	}
	close(p->infilefd);
	close(p->pipefd[1]);
	return (0);
}

int	execute_second_command(t_pipex *p, t_tokenize *t)
{
	int	status;

	p->pids[1] = fork();
	if (p->pids[1] == -1)
		error(ERR_FORK, &p);
	if (p->pids[1] == 0)
	{
		close(p->pipefd[1]);
		status = setup_second_command(p);
		if (status != 0)
			exit(status);
		status = execute_command(p, t, p->argv[3]);
		exit(status);
	}
	close(p->outfilefd);
	close(p->pipefd[0]);
	return (0);
}
