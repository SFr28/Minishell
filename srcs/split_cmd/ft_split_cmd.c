/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfraslin <sfraslin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 18:05:34 by sfraslin          #+#    #+#             */
/*   Updated: 2025/03/07 10:02:46 by sfraslin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Copy argument in the list if there are simple/double quotes
static char	*ft_strdup_quote(char *str, char *table)
{
	char	c;
	int		i;

	c = str[0];
	table = (char *)malloc(sizeof(char) * ft_len_cmd(str, c) + 2);
	if (table == NULL)
		return (NULL);
	table[0] = c;
	i = 1;
	while (str[i] != c && str[i])
	{
		table[i] = str[i];
		i++;
	}
	table[i] = c;
	table[++i] = '\0';
	return (table);
}

//Copy argument if there are no quotes
char	*ft_strdup_cmd(char *str, char *table)
{
	int	i;

	i = 0;
	if (str[i] == '\"' || str[i] == '\'')
	{
		table = ft_strdup_quote(&str[i], table);
		return (table);
	}
	table = (char *)malloc(sizeof(char) * ft_len_cmd(str, ' ') + 1);
	if (table == NULL)
		return (NULL);
	while (str[i] && str[i] != ' ' && str[i] != '\"' && str[i] != '\'')
	{
		table[i] = str[i];
		i++;
	}
	table[i] = '\0';
	return (table);
}

//split_cmd function > 25 lines
static char	*ft_sort_cmd(char *str, char **table, int i, int j)
{
	int	len;

	while (str[i] && ft_is_space(str[i]) == 1)
		i++;
	table[j] = ft_strdup_cmd(&str[i], table[j]);
	if (table[j] == NULL)
	{
		ft_freetab_cmd(table);
		return (NULL);
	}
	len = i + ft_strlen(table[j]);
	while (str[len] && str[len] != ' ')
	{
		table[j] = join_cmd(table[j], str, len);
		len = i + ft_strlen(table[j]);
		if (table[j] == NULL)
			return (NULL);
	}
	return (table[j]);
}

//Split arguments with quotes and spaces 
//if an argument == NULL, we write the next one over it
char	**ft_split_cmd(char *str)
{
	char	**table;
	int		i;
	int		j;
	int		count;

	i = 0;
	j = -1;
	count = ft_count_cmd(str, 0, 1, 0);
	if (count == 0)
		return (NULL);
	table = (char **)malloc(sizeof(char *) * (count + 1));
	if (table == NULL)
		return (NULL);
	while (++j < count && str[i])
	{
		while (str[i] && ft_is_space(str[i]) == 1)
			i++;
		table[j] = ft_sort_cmd(str, table, i, j);
		if (table[j] == NULL)
			return (NULL);
		i += ft_strlen(table[j]);
	}
	table[j] = 0;
	return (table);
}
