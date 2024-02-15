/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 11:46:13 by lkilpela          #+#    #+#             */
/*   Updated: 2024/02/15 21:15:25 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// grep Hello | awk "'{count++} END {print count}'" 
void	start_new_argument(t_tokenize *t) 
{
	char	**new_args;
	int		i;

	i = 0;
	if (!t->in_quotes && (*t->arg != ' ')) 
	{
		t->arg_count++;
		// Allocate a new larger array
		new_args = malloc(sizeof(char *) * t->arg_count);
		if (new_args == NULL)
			error(ERR_MEM);
		// Copy the old elements to the new array
		while (i < t->arg_count - 1) 
		{
			new_args[i] = t->args[i];
			i++;
		}
		// Add the new argument to the new array
		new_args[t->arg_count - 1] = t->arg;
		// Free the old array
		free(t->args);
		// Use the new array
		t->args = new_args;
	}
}

void handle_quotes_and_backslashes(t_tokenize *t) 
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
        t->in_quotes = !t->in_quotes;
    }
}

void end_argument(t_tokenize *t) {
	if (!t->in_quotes && (*t->arg == ' ')) 
	{
		*t->arg = '\0';
	}
}

void null_terminate_array(t_tokenize *t) 
{
	t->arg_count++;
	t->args = realloc(t->args, sizeof(char *) * t->arg_count);
	if (t->args == NULL) 
		return (NULL);
	t->args[t->arg_count - 1] = NULL;
}

char **tokenize(t_tokenize *t) 
{
	t_tokenize t = {0, 0, 0, NULL, NULL, ft_strdup(str)};
	t->arg = t->new_str;

	while (*t->arg) 
	{
		start_new_argument(&t);
		handle_quotes_and_backslashes(&t);
		end_argument(&t);
		t->arg++;
	}
	null_terminate_array(&t);
	return (t->args);
}