/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 11:49:47 by lkilpela          #+#    #+#             */
/*   Updated: 2024/02/29 15:05:32 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	handle_syntax(t_pipex *p)
{
	if (p->argc != 5)
		error(ERR_SYNTAX);
	if (ft_strlen(p->argv[1]) == 0 || ft_strlen(p->argv[4]) == 0)
		error(ERR_FILENAME);
	if (ft_strlen(p->argv[2]) == 0 || ft_strlen(p->argv[3]) == 0)
		error(ERR_CMD_INVALID);
}

void	setup_pipe(t_pipex *p)
{
	if (pipe(p->pipefd) == -1)
		error(ERR_PIPE);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	p;

	init(argc, argv, envp, &p);
	handle_syntax(&p);
	setup_pipe(&p);
	return (0);
}
