/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mestefan <mestefan@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 01:20:11 by mestefan          #+#    #+#             */
/*   Updated: 2025/02/10 01:20:16 by mestefan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../headers/built_in.h"
#include "../../headers/minishell.h"

int	ft_newline(char *av)
{
	int	i;

	i = 0;
	if (av && av[i++] == '-')
	{
		while (av[i])
		{
			if (av[i] != 'n')
				break ;
			if (av[i + 1] == '\0')
				return (true);
			i++;
		}
	}
	return (false);
}

int	ft_is_valid_env_name(const char *name)
{
	int	i;

	i = 0;
	if (!name || !name[0])
		return (0);
	if (!ft_isalpha(name[0]) && name[0] != '_')
		return (0);
	i = 1;
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	print_echo_args(char **args, int i)
{
	char	*expanded_arg;

	while (args[i])
	{
		expanded_arg = ft_strdup(args[i]);
		if (write(STDOUT_FILENO, expanded_arg, ft_strlen(expanded_arg)) < 0)
		{
			free(expanded_arg);
			return (1);
		}
		if (args[i + 1] && write(STDOUT_FILENO, " ", 1) < 0)
		{
			free(expanded_arg);
			return (1);
		}
		free(expanded_arg);
		i++;
	}
	return (0);
}

int	handle_echo(struct s_tree_node *node, t_context *msh)
{
	int		i;
	int		n;

	signal(SIGPIPE, SIG_IGN);
	(void)msh;
	i = 1;
	n = false;
	if (!node || !node->data.exec_u.args)
		return (1);
	while (node->data.exec_u.args[i] && ft_newline(node->data.exec_u.args[i]))
	{
		n = true;
		i++;
	}
	if (print_echo_args(node->data.exec_u.args, i))
		return (1);
	if (!n && write(STDOUT_FILENO, "\n", 1) < 0)
		return (1);
	return (0);
}
