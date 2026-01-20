/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfraslin <sfraslin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 11:24:42 by sovincen          #+#    #+#             */
/*   Updated: 2025/03/06 19:49:41 by sfraslin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Check if minishell have already be launch or if its the first time
//If it's not the first time return 1, else return 0
static int	check_iteration(t_env **env_ms)
{
	t_env	*node;

	node = *env_ms;
	while (node != NULL)
	{
		if (ft_strncmp(node->name, "ITER", 6) == 0)
			return (1);
		node = node->next;
	}
	node = new_envvar("ITER", "1", 1);
	if (node != NULL)
	{
		node->next = *env_ms;
		*env_ms = node;
	}
	return (0);
}

//Modify the SHLVL environment variable according to the actual
//level of minishell
void	adjust_shlvl(t_env **env_ms)
{
	int			lvl;
	t_env		*node;

	if (check_iteration(env_ms) == 0)
		return ;
	node = *env_ms;
	while (node && ft_strncmp(node->name, "SHLVL", 6) != 0)
		node = node->next;
	lvl = ft_atoi(node->var);
	if (node->env_type == 0)
	{
		free(node->name);
		free(node->var);
	}
	lvl++;
	node->name = "SHLVL";
	node->var = ft_itoa(lvl);
	node->env_type = 1;
}

//Initialise a minimal environment for the case of the program is launch 
//without any environment
static void	init_minienv(t_env **env_ms)
{
	t_env	*env_var;

	env_var = new_envvar("PWD", getcwd(NULL, 0), 1);
	env_addback(env_ms, env_var);
	env_var = new_envvar("SHLVL", "1", 1);
	env_addback(env_ms, env_var);
	env_var = new_envvar("_", "/usr/bin/env", 1);
	env_addback(env_ms, env_var);
}

//When an error occur, free the part of the environment already initialise
//And initialise the environment with the minimal value
static void	error_init_env(t_env **env_ms)
{
	clear_env(env_ms);
	ft_putstr_fd("\e[31;1m WARNING :\e[0m", 2);
	ft_putendl_fd("\e[31m Minishell use a minimal environment\e[0m", 2);
	ft_putendl_fd("Failed to initialise environment : allocation failed", 2);
	init_minienv(env_ms);
}

//Initialise the chained list with all environment variable
//If the environment is NULL, provide a minimal environment
void	init_env(int argc, char **argv, char **env, t_env **env_ms)
{
	int		i;
	char	**temp;
	t_env	*env_var;

	(void)argc;
	(void)argv;
	i = -1;
	if (env[0] == NULL)
	{
		ft_putstr_fd("\e[31;1m WARNING :\e[0m", 2);
		ft_putendl_fd("\e[31m Usage of a minimal environment\e[0m", 2);
		init_minienv(env_ms);
	}
	while (env[++i])
	{
		temp = split_env(env[i]);
		if (temp == NULL)
		{
			error_init_env(env_ms);
			return ;
		}
		env_var = new_envvar(temp[0], temp[1], 0);
		env_addback(env_ms, env_var);
		free(temp);
	}
}
