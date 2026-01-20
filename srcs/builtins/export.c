/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sovincen <sovincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 10:07:27 by sovincen          #+#    #+#             */
/*   Updated: 2025/03/05 15:47:07 by sovincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Check the format of the variable name 
//A name could not begin with '=' or a digit
//A name can only contain alphanum charater or '_'
//Return 1 if the name is valid
//Return 0 and print an error message if not
static int	check_name_var(char *args)
{
	int	i;

	i = 0;
	if (args[i] == '=' || ft_isdigit(args[i]) != 0)
	{
		ft_putstr_fd("export: ", 2);
		ft_putstr_fd(args, 2);
		ft_putendl_fd(": not a valid identifier", 2);
		return (0);
	}
	while (args[i] && args[i] != '=')
	{
		if (!(ft_isalnum(args[i]) != 0 || args[i] == '_'))
		{
			ft_putstr_fd("export: ", 2);
			ft_putstr_fd(args, 2);
			ft_putendl_fd(": not a valid identifier", 2);
			return (0);
		}
		i++;
	}
	return (1);
}

//Check if there is an '=' in the arg given
//Return 1 if true
//Return 0 if false
static int	check_equal(char *args)
{
	int	i;

	i = 0;
	while (args != NULL && args[i])
	{
		if (args[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

//Replace the value of one environment variable with a new value
static int	replace_env(t_env *var, char **to_replace)
{
	int	len_name;

	len_name = ft_strlen(to_replace[0]);
	if (ft_strncmp(to_replace[0], var->name, len_name) == 0)
	{
		if (var->env_type == 0)
			free(var->var);
		var->var = to_replace[1];
		var->env_type = 0;
		free(to_replace[0]);
		free(to_replace);
		return (1);
	}
	return (0);
}

//Add or replace the new environment variable
static int	export_var(char *args, t_env **env_ms)
{
	t_env	*node;
	t_env	*new_var;
	char	**var;

	var = split_env(args);
	if (var == NULL)
		return (1);
	node = *env_ms;
	while (node != NULL)
	{
		if (replace_env(node, var) == 1)
			return (0);
		node = node->next;
	}
	new_var = new_envvar(var[0], var[1], 0);
	env_addback(env_ms, new_var);
	free(var);
	return (0);
}

//Initialise a new environment variable and set it's value if given
//If the variable already exist in the environment, update its value
int	ft_export(char **args, t_env **env_ms)
{
	int		status;
	int		i;

	i = 0;
	status = 0;
	while (args[++i])
	{
		while (check_name_var(args[i]) == 0)
		{
			i++;
			status = 1;
			if (args[i] == NULL)
				return (status);
		}
		while (check_equal(args[i]) == 0)
		{
			i++;
			if (args[i] == NULL)
				return (status);
		}
		if (export_var(args[i], env_ms) == 1)
			return (1);
	}
	return (status);
}
