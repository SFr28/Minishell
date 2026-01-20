/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sovincen <sovincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 10:12:53 by sovincen          #+#    #+#             */
/*   Updated: 2025/03/03 16:59:43 by sovincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	unset_a_var(char *arg, t_env **env_ms)
{
	t_env	*var;
	t_env	*to_delete;
	int		len_name;

	var = *env_ms;
	len_name = ft_strlen(arg);
	if (ft_strncmp(var->name, arg, len_name + 1) == 0)
	{
		*env_ms = var->next;
		delone_env(var);
		return ;
	}
	while (var != NULL && var->next != NULL)
	{
		if (ft_strncmp(var->next->name, arg, len_name + 1) == 0)
		{
			to_delete = var->next;
			var->next = var->next->next;
			delone_env(to_delete);
			break ;
		}
		var = var->next;
	}
}

//Delete the environment variable with the same name as the one given as args[1]
int	ft_unset(char **args, t_env **env_ms)
{
	int		i;

	i = 1;
	while (args && args[i])
	{
		unset_a_var(args[i], env_ms);
		i++;
	}
	return (0);
}
