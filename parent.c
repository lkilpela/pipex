/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:41:17 by lkilpela          #+#    #+#             */
/*   Updated: 2024/02/28 13:41:42 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void   redirect_output(char *outfile)
{
    int fd;

    fd = open(outfile, O_CREAT | O_WRONLY | O_TRUNC, PERMISSIONS);
    if (fd == -1)
        error(ERR_OPEN);
    if (dup2(fd, STDOUT_FILENO) == -1)
        error(ERR_DUP2);
    if (close(fd) == -1)
        error(ERR_CLOSE);    
}