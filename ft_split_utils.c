/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfraslin <sfraslin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 18:05:34 by sfraslin          #+#    #+#             */
/*   Updated: 2025/02/10 15:01:06 by sfraslin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stddef.h>

#include <stdio.h>

int  ft_quote(char *str, int i);
int ft_count_cmd(char *str, int i, int count);
int  ft_len_cmd(char *str, char c);
char *ft_strup_quote(char *str, char *tab);
char *ft_strup_cmd(char *str, char *tab);
int ft_strlen(char *str);
char	**ft_freetab_cmd(char **tab, int i);
char    *ft_sort_cmd(char *str, char **tab, int i);

int ft_count_cmd(char *str, int i, int count)
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
        }
        if (!str[i] && str[i - 1] != 34 && str[i - 1] != 39)
            return (0);
		if (str[i] == 32 && str[i + 1] != 32 && str[i + 1] != '\0')
			count++;
        i++;
    }
    printf("count: %d\n", count);
    return (count);
}

int  ft_quote(char *str, int i)
{
    int count;

    count = 0;
    i++;
    if (str[i - 1] == 34)
    {
        count++;
        while (str[i] && str[i] != 34)
            i++;
        if (!str[i])
            return (0);
        i++;
    }
    if (str[i - 1] == 39)
    {
        count++;
        while (str[i] && str[i] != 39)
            i++;
        if (!str[i])
            return (0);
        i++;
    }
    return (count);
}

int ft_strlen(char *str)
{
    int i;

    i = 0;
    while (str[i])
        i++;
    return(i);
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

int  ft_len_cmd(char *str, char c)
{
    int i;

    i = 0;
    if (str[i] == 34 || str[i] == 39)
        i++;
    while (str[i] && str[i] != c)
        i++;
    return (i);
}
