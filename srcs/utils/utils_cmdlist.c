/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cmdlist.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sovincen <sovincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:32:06 by sovincen          #+#    #+#             */
/*   Updated: 2025/03/03 16:52:02 by sovincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "macros.h"

//Return the number of command in the command chained list
int	cmdlist_size(t_cmd **cmds_list)
{
	t_cmd	*cmd;
	int		nb_cmd;

	nb_cmd = 0;
	cmd = *cmds_list;
	while (cmd != NULL)
	{
		nb_cmd++;
		cmd = cmd->next;
	}
	return (nb_cmd);
}

int	check_cmds(char **cmd)
{
	int	i;

	i = 1;
	while (cmd && cmd[i] && cmd[i - 1])
	{
		if ((cmd[i][0] == '<' && cmd[i - 1][0] == '<')
			|| (cmd[i][0] == '>' && cmd[i - 1][0] == '>'))
			return (-1);
		i++;
	}
	return (0);
}

//Compare the part after the last '/' in a string with an 
static int	ft_strncmp_after_bs(char *arg, char *str)
{
	int	i;
	int	pos;

	i = 0;
	pos = 0;
	while (arg && arg[i])
	{
		if (arg[i] == '/')
			pos = i + 1;
		i++;
	}
	if (arg && arg[pos] && ft_strncmp(&arg[pos], str, INT_MAX) == 0)
		return (0);
	return (1);
}

int	check_for_rm(t_cmd *cmd)
{
	int	i;

	if (cmd->path && ft_strncmp_after_bs(cmd->path, "rm") == 0)
	{
		i = 1;
		while (cmd->args[i])
		{
			if (ft_strncmp_after_bs(cmd->args[i], "minishell") == 0)
			{
				ft_putendl_fd("\e[31;1m FORBIDDEN \e[0m", 2);
				return (1);
			}
			i++;
		}
	}
	return (0);
}
