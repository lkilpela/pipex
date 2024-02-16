/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 11:46:13 by lkilpela          #+#    #+#             */
/*   Updated: 2024/02/16 13:25:35 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// awk "'{count++} END {print count}'" 
/*void	start_new_argument(t_tokenize *t, char *start, int len)
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
}*/

void init_tokenize(t_tokenize *t)
{
	t->count = 0;
	t->in_quotes = 0;
	t->args = NULL;
	t->arg = NULL;
}

char *remove_outer_quotes(char *cmd) // cmd = "awk '{count++} END {print count}'" 
{
	int		len;
	char	*new_str;

	len = ft_strlen(cmd);
	if (len >= 2 && (cmd[0] == '"' && cmd[len -1] == '"') ||
		(cmd[0] == '\'' && cmd[len -1] == '\''));
	{
		new_str = ft_substr(cmd, 1, len -2); // cmd = awk '{count++} END {print count}' 
		return (new_str);
	}
	return (ft_strdup(cmd)); 
}

char	**split_cmd(t_tokenize	*t, char *cmd)
{
	char	*start;
	char	*end;
	char	**words;

	start = cmd;
	end = cmd;
	words = NULL;
	// First pass: count the number of words
	while (*end)
	{
		if (*end == '"' || *end == '\'')
			t->in_quotes = !t->in_quotes;
/* Inside the while loop: This is where most of the resizing happens. 
Each time a space is encountered outside of quotes (indicating the end of a word),
the new_args array is resized to accommodate one more word. The new word is then 
added to the array. 
*/
		else if (*end == ' ' && !t->in_quotes)
		{
			words = resize_array(words, t->count, t->count + 1);
			words[t->count++] = ft_substr(start, 0, end - start);
			start = end + 1;
		}
		end++;		
	}
/* After the while loop: This handles the case where there is a word at the end 
of the string after the last space. If the string doesn't end with a space,
the last word wouldn't be added inside the while loop, so it's added here.
The new_args array is resized to accommodate this last word.
*/
	if (end != start)
	{
		words = resize_array(words, t->count, t->count + 1);
		words[t->count++] = ft_substr(start, 0, end - start);
	}
/* Before returning: This is to add a NULL pointer at the end of the array. 
The new_args array is resized to accommodate one more element, and this last 
element is set to NULL. This is a common convention in C when dealing with 
arrays of pointers, as it allows functions that process the array to know where 
the array ends.
*/
	words = resize_array(words, t->count, t->count + 1);
	words[t->count] = NULL;
	return (words);
}

char	**creat_arg_array(char *cmd)
{
	t_tokenize	t;

	init_tokenize(&t);
	return(split_cmd(&t, cmd));
}