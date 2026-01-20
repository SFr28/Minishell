/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sub_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfraslin <sfraslin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 12:07:21 by sfraslin          #+#    #+#             */
/*   Updated: 2025/03/06 18:15:37 by sfraslin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Copy cmds if there is a redirection
static char	*ft_strcpy_other(char *table, char *cmd)
{
	if ((table[0] == '<' && table[1] == '<')
		|| (table[0] == '>' && table[1] == '>'))
	{
		cmd = malloc(sizeof(char) * 3);
		if (cmd == NULL)
			return (NULL);
		cmd[0] = table[0];
		cmd[1] = table[1];
		cmd[2] = '\0';
		return (cmd);
	}
	cmd = malloc(sizeof(char) * 2);
	if (cmd == NULL)
		return (NULL);
	cmd[0] = table[0];
	cmd[1] = '\0';
	return (cmd);
}

//Copy cmds if there are quote + delete those quotes
char	*ft_strcpy_quote(char *cmd, char *arg)
{
	int	c;
	int	i;
	int	j;

	i = -1;
	j = -1;
	c = 0;
	if (cmd[0] == '\"' && cmd[1] != '\"')
		c = 1;
	arg = malloc(sizeof(char) * (ft_strlen(cmd) + 1));
	if (arg == NULL)
		return (NULL);
	while (cmd[++i])
	{
		while (cmd[i] == '\"' || (cmd[i] == '\'' && c == 0))
			i++;
		if (!cmd[i])
			break ;
		arg[++j] = cmd[i];
	}
	arg[++j] = '\0';
	return (arg);
}

//Copy cmds
static char	*ft_strcpy_cmd(char *table, char *cmd)
{
	int	i;

	i = 0;
	if (table[0] == '|' || table[0] == '>' || table[0] == '<')
	{
		cmd = ft_strcpy_other(table, cmd);
		return (cmd);
	}
	cmd = malloc(sizeof(char) * (ft_strlen(table) + 1));
	if (cmd == NULL)
		return (NULL);
	while (table[i])
	{
		cmd[i] = table[i];
		i++;
	}
	cmd[i] = '\0';
	return (cmd);
}

//Previous function > 25 lines
static int	ft_sub_sub(char *table, char **cmd, int j, t_env **env)
{
	if (check_dollar(table) >= 0)
	{
		cmd[j] = ft_change_var(table, cmd[j], env, 0);
		while (ft_condition(table, cmd, j) == 0)
			cmd[j] = ft_change_var(cmd[j], cmd[j], env, 1);
		return (1);
	}
	cmd[j] = ft_strcpy_cmd(table, cmd[j]);
	if (cmd[j] && cmd[j][0] == 0)
	{
		free(cmd[j]);
		return (0);
	}
	if (ft_condition(table, cmd, j) == 1)
	{
		cmd[j + 1] = ft_strcpy_cmd(&table[1], cmd[j + 1]);
		return (2);
	}
	if (ft_condition(table, cmd, j) == 2)
	{
		cmd[j + 1] = ft_strcpy_cmd(&table[2], cmd[j + 1]);
		return (2);
	}
	return (1);
}

//Split once again, with |, < et >
//Delete quotes, change $
char	**ft_subsplit(char **table, t_env **env)
{
	char	**cmd;
	int		count;
	int		i;
	int		j;

	count = ft_subcount(table);
	cmd = ft_calloc((count + 1), sizeof(void *));
	if (cmd == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (table[i] != 0)
	{
		j += ft_sub_sub(table[i], cmd, j, env);
		i++;
	}
	ft_freetab_cmd(table);
	cmd[count] = 0;
	if (check_cmds(cmd) == -1)
	{
		ft_freetab_cmd(cmd);
		return (NULL);
	}
	return (cmd);
}
