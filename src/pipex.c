/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 11:49:47 by lkilpela          #+#    #+#             */
/*   Updated: 2024/04/04 14:27:18 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	is_directory(char *cmd)
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

static int	validate_command(t_pipex *p, t_command *c, char *cmd)
{
	t_tokenize	t;
	int			is_valid;

	is_valid = 1;
	init_tokenize(&t);
	c->args = split_command(&t, cmd);
	if (c->args == NULL || c->args[0] == NULL)
	{
		error_with_arg(ERR_CMD, c->args[0]);
		is_valid = 0;
	}		
	c->path = find_command(p, c->args[0]);
	if (!c->path)
	{
		error_with_arg(ERR_CMD, c->args[0]);
		is_valid = 0;
	}
	if (access(c->path, X_OK) != 0)
	{
		error_with_arg(ERR_CMD, c->args[0]);
		is_valid = 0;
	}
	return (is_valid);		
}

static int	validate_arguments(t_pipex *p)
{
	int	cmd1_valid;
	int	cmd2_valid;
	
	if (p->argc != 5)
		error(ERR_SYNTAX);
	if (ft_strlen(p->argv[1]) == 0 || ft_strlen(p->argv[4]) == 0)
		error(ERR_FILE);
	if (access(p->argv[1], F_OK) != 0)
		error(ERR_FILE);
	if (is_directory(p->argv[2]) || is_directory(p->argv[3]))
		error(ERR_DIR);
	cmd1_valid = validate_command(p, &p->cmds[0], p->argv[2]);
	cmd2_valid = validate_command(p, &p->cmds[1], p->argv[3]);
	if (!cmd1_valid || !cmd2_valid)
		exit(EXIT_FAILURE);
}

static void	setup_pipe(t_pipex *p)
{
	if (pipe(p->pipefd) == -1)
		error(ERR_PIPE);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	p;
	int		status;

	init_pipex(argc, argv, envp, &p);
	validate_arguments(&p);
	setup_pipe(&p);
	status = wait_children(&p);
	if (status != 0)
	{
		cleanup(&p);
		return (status);
	}
	close(p.pipefd[0]);
	close(p.pipefd[1]);
	cleanup(&p);
	system("leaks pipex");
	return (0);
}
