/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 10:37:58 by lkilpela          #+#    #+#             */
/*   Updated: 2024/02/14 10:47:10 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error(t_error e)
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
    exit(1);
}