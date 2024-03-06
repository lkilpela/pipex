/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 15:40:37 by lkilpela          #+#    #+#             */
/*   Updated: 2024/03/06 14:10:26 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <sys/errno.h>

//1st child: any reads from STDIN: read from the input file, 
//any writes to STDOUT: write to the pipe.
int	setup_first_command(t_pipex *p)
{
	int ret;
	printf("In setup_first_command, p->argv[1] = %s\n", p->argv[1]);
	
	p->infilefd = open(p->argv[1], O_RDONLY);
	printf("open returned %d\n", p->infilefd);
	if (p->infilefd == -1)
		error(ERR_OPEN);

	printf("Before first dup2\n");
	ret = dup2(p->infilefd, STDIN_FILENO);
	printf("First dup2 returned %d, errno = %d\n", ret, errno);
	printf("p->infilefd = %d, STDIN_FILENO = %d\n", p->infilefd, STDIN_FILENO);
	if (ret == -1)
	{
    	printf("dup2 failed, errno = %d\n", errno);
	} else {
    	printf("dup2 succeeded\n");
	}
	//{
		//printf("First dup2 failed\n");
		//close(p->infilefd);
		//error(ERR_DUP2);
	//}
	printf("p->pipefd[1] = %d\n", p->pipefd[1]);
	printf("After first dup2\n");
	
	printf("Before second dup2\n");

	ret = dup2(p->pipefd[1], STDOUT_FILENO);
	printf("Second dup2 returned %d, errno = %d\n", ret, errno);
	printf("p->pipefd[1] = %d, STDOUT_FILENO = %d\n", p->pipefd[1], STDOUT_FILENO);
	printf("After second dup2\n");
	if (ret == -1)
	{
		printf("Second dup2 failed\n");
		close(p->pipefd[1]);
		close(p->infilefd);
		error(ERR_DUP2);
	}
	printf("Exiting setup_first_command\n");
	return (0);
}

//2nd child: any reads from STDIN: read from the pipe, 
//any writes to STDOUT: write to the output file.
int	setup_second_command(t_pipex *p)
{
	p->outfilefd = open(p->argv[p->argc - 1],
			O_CREAT | O_WRONLY | O_TRUNC, PERMISSIONS);
	if (p->outfilefd == -1)
		error(ERR_OPEN);
	if (dup2(p->pipefd[0], STDIN_FILENO) == -1)
	{
		close(p->pipefd[0]);
		error(ERR_DUP2);
	}
	if (dup2(p->outfilefd, STDOUT_FILENO) == -1)
	{
		close(p->pipefd[0]);
		close(p->outfilefd);
		error(ERR_DUP2);
	}
	return (0);
}

int	execute_command( t_pipex *p, t_tokenize *t, char *cmd)
{
	int	status;
	int i;

	p->child_cmd = split_command(t, cmd);
	if (p->child_cmd == NULL || p->child_cmd[0] == NULL)
		error(ERR_CMD_NOT_FOUND);
	p->child_path = find_command(p, p->child_cmd[0]);
	if (!p->child_path)
	{
		free_paths(p->child_cmd);
		error(ERR_CMD_NOT_FOUND);
	}
	// Print the command and arguments before they're passed to execve
    printf("Executing command: %s\n", cmd);
    for (i = 0; p->child_cmd[i] != NULL; i++)
        printf("arg[%d] = %s\n", i, p->child_cmd[i]);

	if (execve(p->child_path, p->child_cmd, p->envp) == -1)
	{
		error(ERR_EXECVE);
		return (-1);
	}
	return (0);
}

int	execute_first_command(t_pipex *p, t_tokenize *t)
{
	int	status;
	
	printf("Before fork, PID = %d\n", getpid());
	p->pids[0] = fork();
	printf("After fork, PID = %d, fork returned %d\n", getpid(), p->pids[0]);
	if (p->pids[0] == -1)
		error(ERR_FORK);
	else if (p->pids[0] == 0)
	{
		printf("In child process, PID = %d\n", getpid());
		printf("Calling setup_first_command\n");
		status = setup_first_command(p);
		printf("setup_first_command returned %d\n", status);
		if (status != 0)
		{
			fprintf(stderr, "setup_first_command failed with status %d\n", status);
			exit(status);// Exit the child process with the error status
		}
		printf("Executing command: %s\n", p->argv[2]);
		status = execute_command(p, t, p->argv[2]);
		printf("execute_command returned %d\n", status);
		if (status != 0)
		{
			fprintf(stderr, "execute_command failed with status %d\n", status);
		}
		exit(status);
	}
	close(p->infilefd);
	close(p->pipefd[1]);// Close the write end of the pipe in the parent process
	return (0);
}

int	execute_second_command(t_pipex *p, t_tokenize *t)
{
	int	status;

	p->pids[1] = fork();
	if (p->pids[1] == -1)
		error(ERR_FORK);
	if (p->pids[1] == 0)
	{
		close(p->pipefd[1]);// Close the write end of the pipe in the second child process
		status = setup_second_command(p);
		if (status != 0)
			exit(status);
		status = execute_command(p, t, p->argv[3]);
		exit(status);
	}
	close(p->outfilefd);
	close(p->pipefd[0]); // Close the read end of the pipe in the parent process
	return (0);
}
