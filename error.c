/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 10:37:58 by lkilpela          #+#    #+#             */
/*   Updated: 2024/02/14 12:39:03 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error(int e)
{
	if (e == ERR_SYNTAX)
		perror("Syntax: ./pipex infile cmd1 cmd2 outfile\n");
	else if (e == ERR_FORK)
		perror("fork failed\n");
	else if (e == ERR_PIPE)
		perror("pipe failed\n");
	else if (e == ERR_DUP2)
		perror("dup2 failed\n");
	else if (e == ERR_EXECVE)
		perror("execve failed\n");
	else if (e == ERR_MALLOC)
		perror("malloc failed\n");
	else if (e == ERR_OPEN)
		perror("open failed\n");
	else if (e == ERR_CLOSE)
		perror("close failed\n");
	else if (e == ERR_READ)
		perror("read failed\n");
	else if (e == ERR_WRITE)
		perror("write failed\n");
	else if (e == ERR_MEM)
		perror("Memory allocation failed\n");
	else
		perror("Unknown error\n");
	exit(EXIT_FAILURE);
}
