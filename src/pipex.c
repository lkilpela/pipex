/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 11:49:47 by lkilpela          #+#    #+#             */
/*   Updated: 2024/03/08 14:10:05 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <signal.h>

static int is_directory (char *cmd)
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

/*static char *trim_cmd(char *cmd)
{
	char *trimmed_cmd;

	if (cmd[0] == ' ')
		return (NULL);
	trimmed_cmd = ft_strtrim(cmd, " ");
	if(trimmed_cmd && trimmed_cmd[0] == '\0')
	{
		free(trimmed_cmd);
		return (NULL);
	}
	return (trimmed_cmd);
}

static void check_trimmed_cmd(char *cmd)
{
	char *trimmed_cmd;

	trimmed_cmd = trim_cmd(cmd);
	if (trimmed_cmd == NULL)
		error(ERR_CMD);
	else
		free(trimmed_cmd);
}

int	is_valid_command(t_pipex *p, char *cmd)
{
	char	*path;
	
	if (cmd == NULL || cmd[0] == '\0')
		return (0);
	path = find_command(p, cmd);
	if (path != NULL)
	{
		free(path);
		return (1);
	}
	return (0);
}*/

static void	validate_arguments(t_pipex *p)
{
	printf("argv[2]: %s\n", p->argv[2]);
	// Syntax errors
	if (p->argc != 5)
		error(ERR_SYNTAX);
	if (ft_strlen(p->argv[1]) == 0 || ft_strlen(p->argv[4]) == 0)
		error(ERR_FILE);
	printf("Start checking argv 2\n");
	if (ft_strlen(p->argv[2]) == 0 || ft_strlen(p->argv[3]) == 0)
		error(ERR_CMD);// "" "wc"

	
	printf("Start checking File existence errors\n");
	//File existence errors
	if (access(p->argv[1], F_OK != 0) || access(p->argv[4], F_OK != 0))
		error(ERR_FILE);
	printf("Start checking is directory errors argv2\n");
	if (is_directory(p->argv[2]) && access(p->argv[2], F_OK) != 0)
		error(ERR_FILE);
	printf("Start checking is directory errors argv3\n");
	if (is_directory(p->argv[3]) && access(p->argv[3], F_OK) != 0)
		error(ERR_FILE);
	printf("Finish File existence errors check\n");
	
	printf("Start Permission errors\n");
	// Permission errors
	if (access(p->argv[1], R_OK != 0))
		error(ERR_PERM);
	if (access(p->argv[4], W_OK != 0))
		error(ERR_PERM);
	printf("Finnish Permission errors\n");

	printf("Start is_valid_commnand check\n");
	if (!is_valid_command(p, p->argv[2]) || !is_valid_command(p, p->argv[3]))
		error(ERR_CMD);
	printf("Finnish is_valid_commnand check\n");
	//else if ((access(p->argv[2], X_OK) != 0 || access(p->argv[3], X_OK) != 0))
		//error(ERR_CMD_NOT_EXECUTABLE);*/
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


	/*if (ft_strncmp(p->argv[2], " ", 1 ) == 0 || ft_strncmp(p->argv[3], " ", 1 ) == 0)
		error(ERR_CMD);//" ls" "wc" or " " "wc"
	else
	{
		printf("Start checking trimmed argv 2\n");
		char *trimmed_argv2 = trim_cmd(p->argv[2]);
		char *trimmed_argv3 = trim_cmd(p->argv[3]);
		if (trimmed_argv2 == NULL || trimmed_argv3 == NULL)
			error(ERR_CMD); // "  " "wc" or "   " "wc"
		else
		{
			check_trimmed_cmd(trimmed_argv2);
			check_trimmed_cmd(trimmed_argv3);
		}
		free(trimmed_argv2);
		free(trimmed_argv3);
		printf("Finish checking trimmed argv 2\n");
	}
	printf("Finish syntax errors check\n");*/