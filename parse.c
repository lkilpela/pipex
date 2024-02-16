/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 11:46:13 by lkilpela          #+#    #+#             */
/*   Updated: 2024/02/16 08:47:07 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// awk "'{count++} END {print count}'" 
void	start_new_argument(t_tokenize *t)
{
	char	**new_args;
	int		i;

	i = 0;
	if (!t->in_quotes && (*t->arg != ' '))
	{
		t->count++;
		// Allocate a new larger array
		new_args = malloc(sizeof(char *) * (t->count + 1));
		if (new_args == NULL)
			error(ERR_MEM);
		// Copy the old elements to the new array
		while (i < t->count - 1)
		{
			new_args[i] = t->args[i];
			i++;
		}
		// Add the new argument to the new array
		new_args[t->count - 1] = t->arg;
		// Free the old array
		free(t->args);
		// Use the new array
		t->args = new_args;
	}
}

void	handle_quotes_and_backslashes(t_tokenize *t)
{
	if (t->backslash)
	{
		t->backslash = 0;
	}
	else if (*t->arg == '\\')
	{
		t->backslash = 1;
	}
	else if (*t->arg == '"')
	{
		t->in_quotes = !t->in_quotes;//! operator to toggle a boolean value
	}
}

void	end_argument(t_tokenize *t)
{
	if (!t->in_quotes && (*t->arg == ' '))
		*t->arg = '\0';
}

void	null_terminate_array(t_tokenize *t)
{
	t->count++;
	t->args = malloc(t->args, sizeof(char *) * (t->count + 1));
	if (t->args == NULL)
		return (NULL);
	t->args[t->count - 1] = NULL;
}

char	**parse_command(char *cmd)
{
	t_tokenize	t;

	t.in_quotes = 0;
	t.backslash = 0;
	t.count = 0;
	t.args = NULL;
	t.arg = NULL;
	t.new_str = ft_strdup(cmd);
	if (t.new_str == NULL)
		error(ERR_MEM);
	t.arg = t.new_str;
	while (*t.arg)
	{
		start_new_argument(&t);
		handle_quotes_and_backslashes(&t);
		end_argument(&t);
		t.arg++;
	}
	
	return (t.args);
}
