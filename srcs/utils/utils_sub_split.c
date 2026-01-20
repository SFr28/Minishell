/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_sub_split.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfraslin <sfraslin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:26:48 by sovincen          #+#    #+#             */
/*   Updated: 2025/03/10 11:27:45 by sfraslin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_condition(char *table, char **cmd, int j)
{
	if (cmd[j] && table[0] != '\'' && check_dollar(cmd[j]) >= 0)
		return (0);
	if ((table[0] == '|' || (table[0] == '>' && table[1] != '>')
			|| (table[0] == '<' && table[1] != '<')) && table[1] != '\0')
		return (1);
	if (((table[0] == '<' && table[1] == '<') || (table[0] == '>'
				&& table[1] == '>')) && table[2] != '\0')
		return (2);
	return (-1);
}

int	count_quotes(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'')
		{
			i++;
			while (str[i] && str[i] != '\'')
				i++;
			if (!str[i])
				return (0);
		}
		if (str[i] == '\"')
		{
			i++;
			while (str[i] && str[i] != '\"')
				i++;
			if (!str[i])
				return (0);
		}
	}
	return (1);
}
