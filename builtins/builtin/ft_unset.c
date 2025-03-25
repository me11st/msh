/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alramire <alramire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 01:21:48 by mestefan          #+#    #+#             */
/*   Updated: 2025/03/08 18:32:24 by alramire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/built_in.h"
#include "../../headers/minishell.h"

int	ms_unset_export(t_context *msh, const char *key)
{
	int		i;
	size_t	key_len;
	char	*to_free;

	i = 0;
	key_len = ft_strlen(key);
	while (msh->env_export[i])
	{
		if (ft_strncmp(msh->env_export[i], key, key_len) == 0
			&& msh->env[i][key_len] == '=')
		{
			to_free = msh->env_export[i];
			while (msh->env_export[i + 1])
			{
				msh->env_export[i] = msh->env_export[i + 1];
				i++;
			}
			msh->env_export[i] = NULL;
			free(to_free);
			return (0);
		}
		i++;
	}
	return (-1);
}

int	unset_variable(t_context *msh, const char *var)
{
	if (!is_valid_key(var))
	{
		fprintf(stderr, "unset: `%s`: invalid parameter name\n", var);
		return (1);
	}
	ms_unset_env(msh, var);
	ms_unset_export(msh, var);
	return (0);
}

int	handle_unset(t_tree_node *node, t_context *msh)
{
	char	**av;
	int		i;
	int		status;

	av = node->data.exec_u.args;
	i = 1;
	status = 0;
	while (av[i])
		status |= unset_variable(msh, av[i++]);
	return (msh->ret_exit = status);
}
