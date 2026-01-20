/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfraslin <sfraslin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:01:16 by sovincen          #+#    #+#             */
/*   Updated: 2025/03/06 19:28:31 by sfraslin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Return an error (1), if the first token of the list is a pipe,
//the last token of the list is a pipe, or a pipe is directly follow by another
//pipe
static int	check_tokens(t_token **tokens)
{
	t_token	*node;

	node = *tokens;
	if (node->token == 2)
		return (1);
	while (node != NULL)
	{
		if (node->token == 2 && (node->next == NULL || node->next->token == 2))
			return (1);
		node = node->next;
	}
	return (0);
}

//Display a syntax error message and free if it's necessary
static void	error_syntax(char **cmd, t_token **tokens)
{
	ft_putendl_fd("Syntax error", 2);
	if (cmd != NULL)
		ft_freetab_cmd(cmd);
	if (tokens != NULL)
		ft_free_tokens(tokens);
}

//Split the line in different pieces, get a token list based on them
//Look for syntax error in parsing or token ordrer
//Build the command list based on the type of token stock in the tokens list
static t_cmd	**token_parse(char *line, t_env **env_ms)
{
	char	**table;
	char	**cmd;
	t_token	*tokens;
	t_cmd	**built_cmds;

	table = ft_split_cmd(line);
	if (table == NULL)
		return (NULL);
	cmd = ft_subsplit(table, env_ms);
	if (cmd == NULL)
		return (NULL);
	tokens = NULL;
	if (ft_parsing(&cmd[0], &tokens) == NULL || check_tokens(&tokens) != 0)
	{
		error_syntax(cmd, &tokens);
		return (0);
	}
	ft_freetab_cmd(cmd);
	built_cmds = build_cmds(&tokens, env_ms);
	ft_free_tokens(&tokens);
	return (built_cmds);
}

//If the line is NULL, return -1
//Else, add the line to the history
//Then, build a command list based on this line
//If the command list is not NULL, execute the command list
int	treat_line(char *line, t_env **env_ms)
{
	t_cmd	**built_cmds;

	if (line == NULL)
	{
		printf("exit\n");
		return (1);
	}
	if (line[0])
	{
		add_history(line);
		built_cmds = token_parse(line, env_ms);
		free(line);
		if (built_cmds != NULL)
			execution(built_cmds, env_ms);
	}
	return (0);
}
