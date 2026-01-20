/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfraslin <sfraslin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 10:32:55 by sfraslin          #+#    #+#             */
/*   Updated: 2025/03/03 10:30:58 by sfraslin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_new_token(char *cmd)
{
	t_token	*element;

	element = malloc(sizeof(t_token));
	if (element == NULL)
		return (NULL);
	element->token = 0;
	ft_set_token(cmd, element);
	element->argv = NULL;
	element->infile = NULL;
	element->outfile = NULL;
	element->next = NULL;
	element->argc = 0;
	return (element);
}

void	ft_token_add_back(t_token **token, t_token *new)
{
	t_token	*temp;

	if (new == NULL)
		return ;
	if (*token == NULL)
	{
		*token = new;
		return ;
	}
	temp = ft_last_token(*token);
	temp->next = new;
}

t_token	*ft_last_token(t_token *token)
{
	if (token == NULL)
		return (NULL);
	while (token->next != NULL)
		token = token->next;
	return (token);
}

//Check if we have a pipe, cmds or a redirection
void	ft_set_token(char *cmd, t_token *element)
{
	if (cmd[0] == '|')
		element->token = 2;
	else if (cmd[0] == '<' && cmd[1] == '\0')
		element->token = 1;
	else if (cmd[0] == '<' && cmd[1] == '<')
		element->token = 11;
	else if (cmd[0] == '>' && cmd[1] == '\0')
		element->token = -1;
	else if (cmd[0] == '>' && cmd[1] == '>')
		element->token = -11;
	else
		element->token = 0;
}

void	ft_free_tokens(t_token **tokens)
{
	t_token	*temp;
	int		i;

	while ((*tokens) != NULL)
	{
		i = 0;
		if ((*tokens)->argv != NULL)
		{
			while ((*tokens)->argv[i])
				i++;
			ft_freetab_cmd((*tokens)->argv);
		}
		if ((*tokens)->infile)
			free((*tokens)->infile);
		if ((*tokens)->outfile)
			free((*tokens)->outfile);
		temp = (*tokens)->next;
		free(*tokens);
		*tokens = temp;
	}
}
