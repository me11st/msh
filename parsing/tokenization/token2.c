/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mestefan <mestefan@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 21:15:29 by mestefan          #+#    #+#             */
/*   Updated: 2025/02/15 21:19:06 by mestefan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

bool	escape_special_chars(t_scanner *self)
{
	if (*self->char_itr.cursor == '\\')
	{
		self->char_itr.cursor++;
		return (true);
	}
	return (false);
}

static void	handle_escaped_char(t_scanner *self, char **temp)
{
	char	escaped_str[2];

	self->char_itr.cursor++;
	if (*self->char_itr.cursor == '\\'
		|| *self->char_itr.cursor == '$'
		|| *self->char_itr.cursor == '"'
		|| *self->char_itr.cursor == '\'') 
	{
		escaped_str[0] = *self->char_itr.cursor;
		escaped_str[1] = '\0';
		*temp = ft_strjoin_free_s1(*temp, escaped_str);
	}
	else
	{
		escaped_str[0] = *self->char_itr.cursor;
		escaped_str[1] = '\0';
		*temp = ft_strjoin_free_s1(*temp, escaped_str);
	}
	self->char_itr.cursor++;
}

static void	handle_quotes_and_escape(t_scanner *self, char **temp)
{
	if (*self->char_itr.cursor == '"')
	{
		*temp = ft_strjoin_free_s1(*temp,
				double_quote_token(self).lexeme.start);
		free (self->next.lexeme.ptr);
		self->next.lexeme.ptr = NULL;
	}
	else if (*self->char_itr.cursor == '\'')
	{
		*temp = ft_strjoin_free_s1(*temp,
				single_quote_token(self).lexeme.start);
		free (self->next.lexeme.ptr);
		self->next.lexeme.ptr = NULL;
	}
	else if (*self->char_itr.cursor == '\\' && *(self->char_itr.cursor + 1))
		handle_escaped_char(self, temp);
}

static void	append_normal_char(t_scanner *self, char **temp)
{
	char	*new_char;
	char	*joined;

	if (self->char_itr.cursor && *self->char_itr.cursor)
	{
		new_char = ft_substr(self->char_itr.cursor, 0, 1);
		if (!new_char)
			return ;
		if (*temp == NULL)
			*temp = ft_strdup("");
		if (!*temp)
		{
			free(new_char);
			return ;
		}
		joined = ft_strjoin(*temp, new_char);
		free(new_char);
		free(*temp);
		if (!joined)
		{
			return ;
		}
		*temp = joined;
		self->char_itr.cursor++;
	}
}

t_token	non_delimited_token(t_scanner *self)
{
	char	*temp;

	temp = ft_strdup("");
	if (!self->char_itr.cursor)
	{
		free(temp);
		return ((t_token){0});
	}
	while (*self->char_itr.cursor
		&& !ft_strchr(" \t\n|><", *self->char_itr.cursor))
	{
		if (*self->char_itr.cursor == '"' || *self->char_itr.cursor == '\''
			|| (*self->char_itr.cursor == '\\'))
			handle_quotes_and_escape(self, &temp);
		else
			append_normal_char(self, &temp);
	}
	self->next.type = WORD;
	self->next.lexeme.start = temp;
	self->next.lexeme.ptr = temp;
	self->next.lexeme.length = ft_strlen(temp);
	return (self->next);
}
