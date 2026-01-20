/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sovincen <sovincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 09:32:14 by sfraslin          #+#    #+#             */
/*   Updated: 2025/03/06 14:41:35 by sovincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Create new node of token
t_cmd	*ft_new_cmd(t_token *temp)
{
	t_cmd	*element;

	element = ft_calloc(1, sizeof(t_cmd));
	if (element == NULL)
		return (NULL);
	element->fd_in = 0;
	element->fd_out = 1;
	element->pid = 0;
	if (temp->token == 1 || temp->token == 11)
	{
		element->fd_in = open_file(temp->infile, temp->token);
		if (temp->token == 11 && temp->next == NULL)
		{
			free(element);
			return (NULL);
		}
	}
	else if (temp->token == 0)
		ft_complete_cmd(element, temp);
	else if (temp->token == -1 || temp->token == -11)
		element->fd_out = open_file(temp->outfile, temp->token);
	return (element);
}

//Handle word token
static void	ft_complete_cmd_redir(t_cmd *element, t_token *temp)
{
	if (temp->token == 1 || temp->token == 11)
	{
		if (element->fd_in != 0)
			close(element->fd_in);
		element->fd_in = open_file(temp->infile, temp->token);
	}
	else if (temp->token == -1 || temp->token == -11)
	{
		if (element->fd_out != 1)
			close(element->fd_out);
		element->fd_out = open_file(temp->outfile, temp->token);
	}
}

//Complete node with args, fd_in and fd_out
void	ft_complete_cmd(t_cmd *element, t_token *temp)
{
	int	i;

	while (element->next != NULL)
		element = element->next;
	if (temp->token == 1 || temp->token == 11 || temp->token == -1
		|| temp->token == -11)
		ft_complete_cmd_redir(element, temp);
	else if (temp->token == 0)
	{
		i = 0;
		element->args = (char **)malloc(sizeof(char *) * (temp->argc + 1));
		if (element->args == NULL)
			return ;
		while (temp->argv[i])
		{
			element->args[i] = ft_pre_memcpy(element->args[i], temp->argv[i]);
			i++;
		}
		element->args[i] = 0;
	}
}

void	ft_cmd_add_back(t_cmd **cmd, t_cmd *new)
{
	t_cmd	*temp;

	if (new == NULL)
		return ;
	if (*cmd == NULL)
	{
		*cmd = new;
		return ;
	}
	temp = *cmd;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new;
}

void	ft_free_cmds(t_cmd **cmds)
{
	t_cmd	*temp;
	int		i;

	temp = *cmds;
	while (temp != NULL)
	{
		i = 0;
		while (temp->args && temp->args[i])
			i++;
		if (temp->args != NULL)
			ft_freetab_cmd(temp->args);
		if (temp->path)
			free(temp->path);
		if (temp->infile)
			free(temp->infile);
		if (temp->outfile)
			free(temp->outfile);
		*cmds = temp->next;
		free(temp);
		temp = *cmds;
	}
	free(cmds);
}
