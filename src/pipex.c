/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 11:49:47 by lkilpela          #+#    #+#             */
/*   Updated: 2024/03/08 08:41:18 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <signal.h>

static int is_directory (const char *cmd)
{
	int	fd;

	fd = open(cmd, O_DIRECTORY);
	if (fd != -1)
	{
		close(fd);
		return (1);
	}
	return (0);
}

static void	validate_arguments(t_pipex *p)
{
	if (p->argc != 5)
		error(ERR_SYNTAX);
	if (ft_strlen(p->argv[1]) == 0 || ft_strlen(p->argv[4]) == 0)
		error(ERR_FILENAME);
	if (ft_strlen(p->argv[2]) == 0 || ft_strlen(p->argv[3]) == 0)
		error(ERR_CMD);
	if (access(p->argv[1], F_OK != 0) || access(p->argv[4], F_OK != 0))
		error(ERR_FILE_OR_CMD_NOT_FOUND);
	else if (access(p->argv[1], R_OK != 0))
		error(ERR_FILE_NOT_READABLE);
	else if (access(p->argv[4], W_OK != 0))
		error(ERR_FILE_NOT_WRITABLE);
	//if (access(p->argv[2], F_OK) != 0 || access(p->argv[3], F_OK) != 0)
		//error(ERR_FILE_OR_CMD_NOT_FOUND);
	if (is_directory(p->argv[2]) || is_directory(p->argv[3]))
		error(ERR_CMD_IS_DIRECTORY);
	//else if ((access(p->argv[2], X_OK) != 0 || access(p->argv[3], X_OK) != 0))
		//error(ERR_CMD_NOT_EXECUTABLE);
}

void	setup_pipe(t_pipex *p)
{
	if (pipe(p->pipefd) == -1)
		error(ERR_PIPE);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex		p;
	int			status;
	t_tokenize	t;

	init_pipex(argc, argv, envp, &p);
	init_tokenize(&t);
	validate_arguments(&p);
	setup_pipe(&p);
	status = wait_children(&p, &t);
	if (status != 0)
	{
		cleanup(&p);
		return (status);
	}
	close(p.pipefd[0]);
	close(p.pipefd[1]);
	free(t.args);
	cleanup(&p);
	return (0);
}
