/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 15:40:37 by lkilpela          #+#    #+#             */
/*   Updated: 2024/03/13 11:19:56 by lkilpela         ###   ########.fr       */
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
		error(ERR_PERM);
	ret = dup2(p->infilefd, STDIN_FILENO);
	if (ret == -1)
	{
		close(p->infilefd);
		error(ERR_DUP2);
	}
	ret = dup2(p->pipefd[1], STDOUT_FILENO);
	if (ret == -1)
	{
		close(p->pipefd[1]);
		close(p->infilefd);
		error(ERR_DUP2);
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
		error(ERR_PERM);
	if (dup2(p->pipefd[0], STDIN_FILENO) == -1)
	{
		close(p->pipefd[0]);
		error(ERR_DUP2);
	}
	if (dup2(p->outfilefd, STDOUT_FILENO) == -1)
	{
		close(p->pipefd[0]);
		close(p->outfilefd);
		error(ERR_DUP2);
	}
	return (0);
}

static int	execute_command( t_pipex *p, t_tokenize *t, char *cmd)
{
	p->child_cmd = split_command(t, cmd);
	if (p->child_cmd == NULL || p->child_cmd[0] == NULL)
		error(ERR_CMD);
	p->child_path = find_command(p, p->child_cmd[0]);
	if (!p->child_path)
	{
		free_paths(p->child_cmd);
		error(ERR_FILE);
	}
	if (ft_strchr(p->child_path, '/') && access(p->child_path, X_OK) != 0)
		error(ERR_FILE);
	if (execve(p->child_path, p->child_cmd, p->envp) == -1)
	{
		error(ERR_EXECVE);
		return (-1);
	}
	return (0);
}

int	execute_first_command(t_pipex *p, t_tokenize *t)
{
	int	status;

	p->pids[0] = fork();
	if (p->pids[0] == -1)
		error(ERR_FORK);
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
		error(ERR_FORK);
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
