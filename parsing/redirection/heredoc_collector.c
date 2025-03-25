/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alramire <alramire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 18:18:13 by alramire          #+#    #+#             */
/*   Updated: 2025/03/08 15:06:06 by alramire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	handle_heredoc_interrupt(t_list *head, const char *delimiter)
{
	(void)delimiter;
	if (is_heredoc_interrupted())
	{
		free_list(head);
	}
}

static char	*read_and_expand_line(const char *delimiter, t_context *msh)
{
	char	*line;
	char	*expanded_line;

	line = readline("heredoc> ");
	if (is_heredoc_interrupted())
	{
		free(line);
		return (NULL);
	}
	if (!line)
	{
		if (!line)
			fprintf(stderr, "Warning: HEREDOC delimited by EOF (wanted `%s')\n",
				delimiter);
		return (NULL);
	}
	if (ft_strcmp(line, delimiter) == 0)
	{
		free(line);
		return (NULL);
	}
	expanded_line = expand_env_vars(line, msh);
	free(line);
	return (expanded_line);
}

char	*collect_heredoc_input(const char *delimiter, t_context *msh)
{
	t_list	*head;
	char	*line;
	char	*result;

	head = NULL;
	setup_heredoc_signals();
	reset_heredoc_interrupt();
	while (!is_heredoc_interrupted())
	{
		line = read_and_expand_line(delimiter, msh);
		if (!line || is_heredoc_interrupted())
			break ;
		append_node(&head, line);
		free(line);
	}
	if (is_heredoc_interrupted())
	{
		handle_heredoc_interrupt(head, delimiter);
		restore_global_signals();
		return (NULL);
	}
	result = concatenate_lines(head);
	free_list(head);
	return (result);
}
