/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sovincen <sovincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 13:47:24 by sovincen          #+#    #+#             */
/*   Updated: 2025/02/17 18:09:02 by sovincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Create a new node with the name and the value of a new environment variable
t_env	*new_envvar(char *name, char *var, int env_type)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (new_node == NULL)
		return (NULL);
	new_node->name = name;
	new_node->var = var;
	new_node->env_type = env_type;
	new_node->next = NULL;
	return (new_node);
}

//Add a new environment variable at the end of the chained list
void	env_addback(t_env **env, t_env *new_var)
{
	t_env	*last;

	if (*env == NULL)
		*env = new_var;
	else
	{
		last = *env;
		while (last->next != NULL)
			last = last->next;
		last->next = new_var;
	}
}

//Return the size of the chained list
int	env_size(t_env **env)
{
	int		i;
	t_env	*node;

	i = 0;
	node = *env;
	while (node != NULL)
	{
		i++;
		node = node->next;
	}
	return (i);
}

//Delete one node from the chained list
void	delone_env(t_env *to_delete)
{
	if (to_delete->env_type == 0)
	{
		free(to_delete->name);
		free(to_delete->var);
	}
	free(to_delete);
}

//Clear the env chained list
//Free each node and its content if necessary
void	clear_env(t_env **env)
{
	t_env	*temp;

	while (*env != NULL)
	{
		temp = (*env)->next;
		if ((*env)->env_type == 0)
		{
			free((*env)->name);
			free((*env)->var);
		}
		free(*env);
		*env = temp;
	}
}
