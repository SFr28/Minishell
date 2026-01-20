/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfraslin <sfraslin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 18:05:34 by sfraslin          #+#    #+#             */
/*   Updated: 2025/03/06 18:17:42 by sfraslin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Count number of arrays we will need in split_cmd
int	ft_count_cmd(char *str, int i, int count, int q)
{
	while (str && str[i] && ft_is_space(str[i]) == 1)
		i++;
	if (str == NULL || !str[i])
		return (0);
	while (str && str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
		{
			q = ft_quote(str, i);
			if (q == 0)
				return (0);
			i = q;
			if (str[i] == '\"' || str[i] == '\'')
				i--;
		}
		if (!str[i])
			break ;
		if (ft_is_space(str[i]) == 1 && ft_is_space(str[i + 1]) != 1
			&& str[i + 1] != '\0')
			count++;
		i++;
	}
	return (count);
}

//Count number of arrays we will need in split_cmd if there are quotes
int	ft_quote(char *str, int i)
{
	int	count;

	count = count_quotes(str);
	if (count == 0)
		return (0);
	if (str[i] == '\"')
	{
		i++;
		while (str[i] && str[i] != '\"')
			i++;
		if (!str[i])
			return (i);
		i++;
		return (i);
	}
	else if (str[i] == '\'')
	{
		i++;
		while (str[i] && str[i] != '\'')
			i++;
		if (!str[i])
			return (i);
		i++;
	}
	return (i);
}

//free tab_cmd
char	**ft_freetab_cmd(char **table)
{
	int	i;

	i = 0;
	while (table && table[i])
	{
		free(table[i]);
		i++;
	}
	free(table);
	return (NULL);
}

int	ft_len_cmd(char *str, char c)
{
	int	i;

	i = 0;
	if (str[i] == '\"' || str[i] == '\'')
		i++;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

//Count number of arrays we will need in sub_split_cmd
int	ft_subcount(char **table)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (table && table[i] != 0 && table[i][0])
	{
		if ((table[i][0] == '|' || table[i][0] == '>' ||
		table[i][0] == '<') && table[i][1] != '\0')
			count++;
		count++;
		i++;
	}
	return (count);
}
