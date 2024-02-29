/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 15:40:37 by lkilpela          #+#    #+#             */
/*   Updated: 2024/02/29 14:07:57 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//1st child: any reads from STDIN: read from the input file, 
//any writes to STDOUT: write to the pipe.
void	setup_first_command(t_pipex *p)
{
	p->infilefd = open(p->argv[1], O_RDONLY);
	if (p->infilefd == -1)
		error(ERR_OPEN);
	if (dup2(p->infilefd, STDIN_FILENO) == -1)
		error(ERR_DUP2);
	if (dup2(p->pipefd[1], STDOUT_FILENO) == -1)
		error(ERR_DUP2);
	if (close(p->infilefd) == -1 || close(p->pipefd[1]) == -1)
		error(ERR_CLOSE);
}

//2nd child: any reads from STDIN: read from the pipe, 
//any writes to STDOUT: write to the output file.
void	setup_second_command(t_pipex *p)
{
	p->outfilefd = open(p->argv[p->argc - 1],
			O_CREAT | O_WRONLY | O_TRUNC, PERMISSIONS);
	if (p->outfilefd == -1)
		error(ERR_OPEN);
	if (dup2(p->pipefd[0], STDIN_FILENO) == -1)
		error(ERR_DUP2);
	if (dup2(p->outfilefd, STDOUT_FILENO) == -1)
		error(ERR_DUP2);
	if (close(p->pipefd[0]) == -1 || close(p->outfilefd) == -1)
		error(ERR_CLOSE);
}

void	execute_child( t_pipex *p, t_tokenize *t, char *cmd)
{
	int	status;

	p->child_cmd = split_command(t, cmd);
	if (p->child_cmd == NULL || p->child_cmd[0] == NULL)
		error(ERR_CMD_NOT_FOUND);
	p->child_path = find_command(p, p->child_cmd[0]);
	if (!p->child_path)
	{
		free_paths(p->child_cmd);
		error(ERR_CMD_NOT_FOUND);
	}
	if (execve(p->child_path, p->child_cmd, p->envp) == -1)
		error(ERR_EXECVE);
}

void	execute_first_command(t_pipex *p, t_tokenize *t, char *cmd)
{
	int	status;

	p->pid = fork();
	if (p->pid == -1)
		error(ERR_FORK);
	if (p->pid == 0)
	{
		setup_first_command(p);
		if (execute_child(p, t, p->argv[2]) == -1)
			error(ERR_EXECVE);
	}
	else
	{
		if (waitpid(p->pid, &status, 0) == -1)
			error(ERR_WAITPID);
	}
}

void	execute_second_command(t_pipex *p, t_tokenize *t, char *cmd)
{
	int	status;

	p->pid = fork();
	if (p->pid == -1)
		error(ERR_FORK);
	if (p->pid == 0)
	{
		setup_second_command(p);
		if (execute_child(p, t, p->argv[3]) == -1)
			error(ERR_EXECVE);
	}
	else
	{
		if (waitpid(p->pid, &status, 0) == -1)
			error(ERR_WAITPID);
	}
}
