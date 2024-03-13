/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 11:53:33 by lkilpela          #+#    #+#             */
/*   Updated: 2024/03/13 11:54:31 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_pipex(int argc, char **argv, char **envp, t_pipex *p)
{
	p->argc = argc;
	p->argv = argv;
	p->envp = envp;
	p->infilefd = -1;
	p->outfilefd = -1;
	p->paths = NULL;
	p->child_path = NULL;
	p->child_cmd = NULL;
	p->pids[0] = -1;
	p->pids[1] = -1;
	p->pipefd[0] = -1;
	p->pipefd[1] = -1;
}

void	init_tokenize(t_tokenize *t)
{
	t->count = 0;
	t->in_quotes = 0;
	t->args = NULL;
}
