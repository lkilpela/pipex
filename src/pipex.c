/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 11:49:47 by lkilpela          #+#    #+#             */
/*   Updated: 2024/03/27 08:20:37 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int is_directory (char *cmd)
{
	int	fd;

	//if (access(cmd, F_OK) != 0)
		//error(ERR_FILE);
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
	// Syntax errors
	if (p->argc != 5)
		error(ERR_SYNTAX);
	if (ft_strlen(p->argv[1]) == 0 || ft_strlen(p->argv[4]) == 0)
		error(ERR_FILE);
	if (ft_strlen(p->argv[2]) == 0 || ft_strlen(p->argv[3]) == 0)
		error(ERR_CMD);// "" "wc"

	//File existence errors
	if (access(p->argv[1], F_OK != 0))
		error(ERR_FILE);
	if (is_directory(p->argv[2]) || is_directory(p->argv[3]))
		error(ERR_DIR);
	if (access(p->argv[2], F_OK) != 0 || access(p->argv[3], F_OK) != 0)
		error(ERR_CMD); // Invalid cmd1/cmd2
	
	if ((access(p->argv[2], X_OK) != 0 || access(p->argv[3], X_OK) != 0))
		error(ERR_PERM);
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
