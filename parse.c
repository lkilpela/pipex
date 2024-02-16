/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 11:46:13 by lkilpela          #+#    #+#             */
/*   Updated: 2024/02/16 09:02:07 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// awk "'{count++} END {print count}'" 
void	start_new_argument(t_tokenize *t, char *start, int len)
{
	char	**new_args;
	int		i;

	i = 0;
	if (!t->in_quotes && (*t->arg != ' '))
	{
		t->count++;
		new_args = resize_array(t->args, t->count -1, t->count);
		if (new_args == NULL)
			error(ERR_MEM);
		new_args[t->count - 1] = ft_strndup(start, len); // Add new argument at the end
		if (new_args[t->count - 1] == NULL)
			error(ERR_MEM);
		t->args = new_args; // Use the new array
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
	char	**new_args;
	
	t->count++;
	new_args = resize_array(t->args, t->count -1, t->count);
	if (new_args == NULL)
		return;
	new_args[t->count - 1] = NULL;
	t->args = new_args;
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
