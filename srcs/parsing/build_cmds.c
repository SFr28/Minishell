/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfraslin <sfraslin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:00:49 by sfraslin          #+#    #+#             */
/*   Updated: 2025/03/06 18:24:00 by sfraslin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

//Built cmds in a linked list
t_cmd	**build_cmds(t_token **tokens, t_env **env)
{
	t_cmd	**cmd;
	t_cmd	*element;

	g_status = 0;
	if ((*tokens)->token != 1 && (*tokens)->token != 11
		&& (*tokens)->token != 0)
		return (NULL);
	cmd = ft_calloc(1, sizeof(void *));
	if (cmd == NULL)
		return (NULL);
	element = ft_new_cmd(*tokens);
	if (element == NULL)
	{
		ft_free_cmds(cmd);
		return (NULL);
	}
	ft_cmd_add_back(cmd, element);
	if (ft_create_cmds(cmd, element, (*tokens)->next) == -1)
		return (NULL);
	if (ft_find_cmds(cmd, env) == -1)
	{
		ft_free_cmds(cmd);
		return (NULL);
	}
	return (cmd);
}

//Create cmds (previous function > 25 lines)
int	ft_create_cmds(t_cmd **cmd, t_cmd *element, t_token *temp)
{
	while (temp != NULL)
	{
		if (temp->token == 2)
		{
			element = NULL;
			element = ft_new_cmd(temp);
			if (element == NULL)
				return (-1);
			ft_cmd_add_back(cmd, element);
		}
		else
			ft_complete_cmd(element, temp);
		if (element == NULL)
		{
			ft_free_cmds(cmd);
			return (-1);
		}
		temp = temp->next;
	}
	return (0);
}
