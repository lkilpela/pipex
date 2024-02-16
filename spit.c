/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 13:30:19 by lkilpela          #+#    #+#             */
/*   Updated: 2024/02/16 14:00:19 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_tokenize(t_tokenize *t)
{
	t->count = 0;
	t->in_quotes = 0;
	t->args = NULL;
	t->arg = NULL;
}

void	toggle_quotes(t_tokenize *t, char c)
{
	if (c == '"' || c == '\'')
	t->in_quotes = !t->in_quotes;
}

void	add_word(t_tokenize *t, char *start, char *end)
{
	t->args = resize_array(t->args, t->count, t->count + 1);
	t->args[t->count++] = ft_substr(start, 0, end - start);
}

void	split_on_space(t_tokenize *t, char *cmd)
{
	char	*end;
	char	*start;

	start = cmd;
	end = cmd;
	while (*end)
	{
		toggle_quotes(t, *end);
		if (*end == ' ' && !t->in_quotes)
		{
			add_word(t, start, end);
			start = end + 1;
		}
		end++;
	}
	if (end != start)
		add_word(t, start, end);
}

void    split_command(t_tokenize *t, char *cmd)
{
	char	*start;
	char	*end;

	start = cmd;
	end = cmd;
	split_on_space(t, cmd);
	t->args = resize_array(t->args, t->count, t->count + 1);
	t->args[t->count] = NULL;
}
