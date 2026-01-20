/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfraslin <sfraslin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 11:49:24 by sfraslin          #+#    #+#             */
/*   Updated: 2025/03/06 18:41:26 by sfraslin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Create a linked list of tokens with the matrix created by split
t_token	**ft_parsing(char **cmd, t_token **tokens)
{
	t_token	*temp;
	int		i;

	if (ft_create_tokens(cmd[0], tokens) == -1)
		return (NULL);
	i = 0;
	temp = *tokens;
	while (cmd && cmd[i] != 0)
	{
		temp = ft_last_token(*tokens);
		i = ft_sub_par(cmd, temp, i);
		if (i == -1)
			return (NULL);
		if (cmd[i] == NULL)
			break ;
		if (ft_create_tokens(cmd[i], tokens) == -1)
			return (NULL);
	}
	return (tokens);
}

//Previous function > 25 lines
int	ft_sub_par(char **cmd, t_token *t, int i)
{
	int	count;

	count = 0;
	if (t->token == 1 || t->token == -1
		|| t->token == 11 || t->token == -11)
	{
		ft_file(cmd[i + 1], t);
		if (((t->token == 1 || t->token == 11) && t->infile == NULL)
			|| ((t->token == -1 || t->token == -11) && t->outfile == NULL))
			return (-1);
		i += 2;
	}
	else if (t->token == 2)
		i++;
	else if (t->token == 0)
	{
		i++;
		while (cmd[i + count] != 0 && cmd[i + count][0] != '|'
			&& cmd[i + count][0] != '<' && cmd[i + count][0] != '>')
			count++;
		if (ft_complete_token(cmd, t, count, i) == -1)
			return (-1);
		i += count;
	}
	return (i);
}

//Create token
int	ft_create_tokens(char *cmd, t_token **token)
{
	t_token	*temp;

	if (!cmd)
		return (-1);
	temp = ft_new_token(cmd);
	if (temp == NULL)
		return (-1);
	ft_token_add_back(token, temp);
	return (0);
}

//Copy name of infile/outfile in the token 
void	ft_file(char *cmd, t_token *element)
{
	int	i;
	int	len;

	i = 0;
	if (cmd == NULL)
		return ;
	len = ft_strlen(cmd);
	if (element->token == 1 || element->token == 11)
	{
		element->infile = malloc(sizeof(char) * (len + 1));
		if (element->infile == NULL)
			return ;
		ft_memcpy(element->infile, cmd, len);
		element->infile[len] = '\0';
	}
	if (element->token == -1 || element->token == -11)
	{
		element->outfile = malloc(sizeof(char) * (len + 1));
		if (element->outfile == NULL)
			return ;
		ft_memcpy(element->outfile, cmd, len);
		element->outfile[len] = '\0';
	}
}

//Complete token->argv with the list of cmd
int	ft_complete_token(char **cmd, t_token *element, int count, int i)
{
	int		j;

	j = 0;
	if (i > 0)
		i--;
	element->argc = count + 1;
	element->argv = (char **)malloc(sizeof(char *) * (count + 2));
	if (element->argv == NULL)
		return (-1);
	while (cmd[i] != 0 && cmd[i][0] != '|'
		&& cmd[i][0] != '<' && cmd[i][0] != '>' && j < (count + 1))
	{
		element->argv[j] = ft_strcpy_quote(cmd[i], element->argv[j]);
		if (element->argv[j] == NULL)
			return (-1);
		element->argv[j][ft_strlen(cmd[i])] = '\0';
		i++;
		j++;
	}
	element->argv[count + 1] = 0;
	return (0);
}
