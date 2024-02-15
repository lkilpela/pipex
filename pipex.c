/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 11:49:47 by lkilpela          #+#    #+#             */
/*   Updated: 2024/02/15 15:24:37 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	handle_syntax(t_pipex *p)
{
	if (p->argc != 5)
		error(ERR_SYNTAX);
	return (0);
}
static void	open_files(t_pipex *p)
{
	p->infile = open(p->argv[1], O_RDONLY);
	p->outfile = open(p->argv[p->argc - 1],
				O_CREAT | O_WRONLY | O_TRUNC, PERMISSIONS);
	if (p->infile == -1 || p->outfile == -1)
		error(ERR_OPEN);
}

int	child_process(t_pipex *p)
{
	p->infile = openfiles(&p);
	
}
int main(int argc, char **argv, char **envp)
{
    t_pipex p;

	init(argc, argv, envp, &p);
    handle_syntax(&p);


}
