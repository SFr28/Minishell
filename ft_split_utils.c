/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfraslin <sfraslin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 18:05:34 by sfraslin          #+#    #+#             */
/*   Updated: 2025/02/11 15:24:26 by sfraslin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stddef.h>

#include <stdio.h>

char	*ft_strdup_quote(char *str, char *tab);
char	*ft_strdup_cmd(char *str, char *tab);
char	*ft_sort_cmd(char *str, char *tab, int i);
char	**ft_freetab_cmd(char **tab, int i);
char    **ft_subsplit(char **tab);
char    *ft_strcpy_cmd(char *tab, char *cmd);
char    *ft_strcpy_other(char *tab, char *cmd);
char    *ft_strcpy_quote(char *tab, char *cmd);
int		ft_quote(char *str, int i);
int		ft_count_cmd(char *str, int i, int j);
int		ft_len_cmd(char *str, char c);
int		ft_strlen(char *str);
int     ft_subcount(char **tab);

int	ft_count_cmd(char *str, int i, int count)
{
	while (str[i] && str[i] == 32)
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] == 34 || str[i] == 39)
		{
			count += ft_quote(str, i);
			i++;
			while (str[i] && str[i] != 34 && str[i] != 39)
				i++;
			if (!str[i])
				return (0);
			i++;
			if (!str[i] && str[i - 1] != 34 && str[i - 1] != 39)
				return (0);
		}
		if (str[i] == 32 && str[i + 1] != 32 && str[i + 1] != '\0'
			&& str[i - 1] != 34 && str[i - 1] != 39)
			count++;
		i++;
	}
	return (count);
}

int	ft_quote(char *str, int i)
{
	int	count;

	count = 0;
	if (str[i] == 34)
	{
		i++;
		count++;
		while (str[i] && str[i] != 34)
			i++;
		if (!str[i])
			return (0);
	}
	if (str[i] == 39)
	{
		i++;
		count++;
		while (str[i] && str[i] != 39)
			i++;
		if (!str[i])
			return (0);
	}
	return (count);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	**ft_freetab_cmd(char **tab, int i)
{
	i--;
	while (i >= 0)
	{
		free(tab[i]);
		i--;
	}
	free(tab);
	return (NULL);
}

int	ft_len_cmd(char *str, char c)
{
	int	i;

	i = 0;
	if (str[i] == 34 || str[i] == 39)
		i++;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}
