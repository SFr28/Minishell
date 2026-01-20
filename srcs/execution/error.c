/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sovincen <sovincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:44:04 by sovincen          #+#    #+#             */
/*   Updated: 2025/03/06 15:14:19 by sovincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Clean the command list chained list by freeing all the node
void	clean_cmds(t_cmd **cmd_list)
{
	t_cmd	*node;
	t_cmd	*temp;

	node = *cmd_list;
	while (node != NULL)
	{
		temp = node->next;
		free(node);
		node = temp;
	}	
}

int	error_exit(char *msg_err)
{
	perror(msg_err);
	return (1);
}

//Exit the command line in case of error
int	error_execute(t_cmd *cmd, t_env **env_ms, char **env_arr, int status)
{
	ft_putstr_fd(cmd->args[0], 2);
	if (status == 126)
		ft_putendl_fd(": Permission denied", 2);
	if (status == 127)
		ft_putendl_fd(": command not found", 2);
	if (env_arr != NULL)
		free_split(env_arr);
	clear_env(env_ms);
	return (status);
}
