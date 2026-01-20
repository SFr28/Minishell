/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sovincen <sovincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 11:29:03 by sovincen          #+#    #+#             */
/*   Updated: 2025/02/27 10:38:47 by sovincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Display all environment variable on the standart input
//if they are more than 1 arg ("env"), display an error on standart error and
//return status = 1
int	ft_env(char **args, t_env **env_ms)
{
	t_env	*node;

	node = *env_ms;
	if (ft_count_args(args) > 1)
	{
		ft_putendl_fd("env: too many arguments", 2);
		return (1);
	}
	while (node != NULL)
	{
		ft_putstr_fd(node->name, 1);
		ft_putchar_fd('=', 1);
		ft_putstr_fd(node->var, 1);
		ft_putchar_fd('\n', 1);
		node = node->next;
	}
	return (0);
}
