/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sovincen <sovincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:55:53 by sovincen          #+#    #+#             */
/*   Updated: 2025/03/06 15:12:07 by sovincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Update the PWD and OLD_PWD environment variable
static void	set_new_pwd(char *new_pwd, char *old_pwd, t_env **env_ms)
{
	t_env	*node;
	char	*name;

	node = *env_ms;
	while (node != NULL && ft_strncmp(node->name, "PWD", 3) != 0)
		node = node->next;
	if (node != NULL)
	{
		free(node->var);
		node->var = new_pwd;
	}
	node = *env_ms;
	while (node != NULL && ft_strncmp(node->name, "OLDPWD", 6) != 0)
		node = node->next;
	if (node != NULL)
	{
		free(node->var);
		node->var = old_pwd;
	}
	else
	{
		name = ft_strdup("OLDPWD");
		node = new_envvar(name, old_pwd, 0);
		env_addback(env_ms, node);
	}
}

//Print an error message according to the type of error encontered
static void	error_cd(char *path, int type)
{
	if (type == 0)
		ft_putendl_fd("cd: too many arguments", 2);
	if (type == 1)
		ft_putendl_fd("cd: HOME not set", 2);
	if (type == 2)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putendl_fd(" No such direcory", 2);
	}
	if (type == 3)
		ft_putendl_fd("cd: OLD_PWD not set", 2);
}

//Search for the value of OLDPWD in the environment and return it
//Return NULL if OLDPWD is not set
char	*get_oldpwd(t_env **env_ms)
{
	t_env	*node;

	node = *env_ms;
	while (node != NULL && ft_strncmp(node->name, "OLDPWD", 6) != 0)
		node = node->next;
	if (node == NULL)
		return (NULL);
	return (node->var);
}

//If no path is given as argument, set the new path to HOME
static char	*set_path(char *path_given, t_env **env_ms)
{
	char	*path;

	if (path_given == NULL || path_given[0] == '\0')
	{
		path = getenv("HOME");
		if (path == NULL)
			error_cd(path, 1);
	}
	else if (ft_strncmp(path_given, "-", 2) == 0)
	{
		path = get_oldpwd(env_ms);
		if (path == NULL)
			error_cd(path, 3);
		else
			ft_putendl_fd(path, 2);
	}
	else
		path = path_given;
	return (path);
}

//Change the current working directory
//store the directory before moving in old_pwd
//if no path is given, use the HOME env. var. as a path
//		if HOME is not set, return an error (exit status of 2 because builtins)
int	ft_cd(char **args, t_env **env_ms)
{
	char	*new_pwd;
	char	*old_pwd;
	char	*path;

	if (ft_count_args(args) > 2)
	{
		error_cd(NULL, 0);
		return (1);
	}
	old_pwd = getcwd(NULL, 0);
	path = set_path(args[1], env_ms);
	if (path == NULL)
		return (1);
	if (chdir(path) != 0)
	{
		error_cd(path, 2);
		return (1);
	}
	new_pwd = getcwd(NULL, 0);
	set_new_pwd(new_pwd, old_pwd, env_ms);
	return (0);
}
