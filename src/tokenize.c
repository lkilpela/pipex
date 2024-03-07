/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 13:30:19 by lkilpela          #+#    #+#             */
/*   Updated: 2024/03/07 14:02:21 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_tokenize(t_tokenize *t)
{
	t->count = 0;
	t->in_quotes = 0;
	t->args = NULL;
}

static void	toggle_quotes(t_tokenize *t, char c)
{
	if (c == '"' || c == '\'')
		t->in_quotes = !t->in_quotes;
}

static int	add_word(t_tokenize *t, char *start, char *end)
{
	char	**new_args;

	new_args = resize_array(t->args, t->count, t->count + 1);
	if (!new_args)
		return (-1);
	t->args = new_args;
	t->args[t->count++] = ft_substr(start, 0, end - start);
	return (0);
}

static void	split_on_space(t_tokenize *t, char *cmd)
{
	char	*end;
	char	*start;

	start = cmd;
	end = cmd;
	while (*end)
	{
		if (*end == '"' || *end == '\'')
			toggle_quotes(t, *end);
		if (*end == ' ' && (!t->in_quotes || *(end + 1) == '\0'))
		{
			add_word(t, start, end + (*(end + 1) == '\0'));
			start = end + 1;
		}
		end++;
	}
	if (end != start)
		add_word(t, start, end);
}

//line 66: Return NULL for empty command string
char	**split_command(t_tokenize *t, char *cmd)
{
	char	**new_args;

	if (cmd[0] == '\0')
		return (NULL);
	split_on_space(t, cmd);
	new_args = resize_array(t->args, t->count, t->count + 1);
	if (!new_args)
		return (NULL);
	t->args = new_args;
	t->args[t->count] = NULL;
	return (t->args);
}
