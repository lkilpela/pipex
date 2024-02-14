/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 10:37:58 by lkilpela          #+#    #+#             */
/*   Updated: 2024/02/14 11:36:46 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error(int e)
{
	if (e == ERR_FORK)
		perror("fork failed");
	else if (e == ERR_PIPE)
		perror("pipe failed");
	else if (e == ERR_DUP2)
		perror("dup2 failed");
	else if (e == ERR_EXECVE)
		perror("execve failed");
	else if (e == ERR_MALLOC)
		perror("malloc failed");
	else if (e == ERR_OPEN)
		perror("open failed");
	else if (e == ERR_CLOSE)
		perror("close failed");
	else if (e == ERR_READ)
		perror("read failed");
	else if (e == ERR_WRITE)
		perror("write failed");
	else if (e == ERR_MEM)
		perror("Memory allocation failed");
	else
		perror("Unknown error");
	exit(EXIT_FAILURE);
}