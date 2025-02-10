/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfraslin <sfraslin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 18:05:34 by sfraslin          #+#    #+#             */
/*   Updated: 2025/02/10 14:01:19 by sfraslin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stddef.h>

int  ft_quote(char *str, int i);
int  ft_count_cmd(char *str, int i, int count);
int  ft_len_cmd(char *str, char c);
char *ft_strup_quote(char *str, char *tab);
char *ft_strup_cmd(char *str, char *tab);
char	**ft_freetab_cmd(char **tab, int i);
int ft_strlen(char *str);
char    *ft_sort_cmd(char *str, char *tab, int i);

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

char *ft_strup_quote(char *str, char *tab)
{
    char    c;
    int     i;
    
    tab = (char *)malloc(sizeof(char) * ft_len_cmd(str, str[i]) + 2);
    c = str[0];
    if (tab == NULL)
        return (NULL);
    tab[0] = c;
    i = 1;
    while (str[i] != c && str[i])
	{
		tab[i] = str[i];
		i++;
	}
    tab[i] = c;
	tab[++i] = '\0';
    return (tab);
}

char *ft_strup_cmd(char *str, char *tab)
{
    int i;

    i = 0;
    if (str[i] == 34 || str[i] == 39)
    {
        tab = ft_strup_quote(&str[i], tab);
        return (tab);
    }
    tab = (char *)malloc(sizeof(char) * ft_len_cmd(str, ' ') + 1);
    if (tab == NULL)
        return (NULL);
    while (str[i] && str[i] != ' ' && str[i] != 34 && str[i] != 39)
	{
		tab[i] = str[i];
		i++;
	}
	tab[i] = '\0';
    return (tab);
}

char    **ft_split_cmd(char *str)
{
    char    **tab;
    int     i;
    int     j;
    int count;

    i = 0;
    j = 0;
    count = ft_count_cmd(str, 0, 1);
    if (count == 0)
        return (NULL);
    tab = (char **)malloc(sizeof(char *) * count + 1);
    if (tab == NULL)
        return (NULL);
    while (j < count && str[i])
    {
        tab[j] = ft_sort_cmd(str, tab[j], i);
        i += ft_strlen(tab[j]);
        if (i == 32)
            i++;
        j++;
    }
	tab[j] = 0;
	return (tab);
}

char    *ft_sort_cmd(char *str, char *tab, int i)
{
    while (str[i] && str[i] == 32)
        i++;
    tab = ft_strup_cmd(&str[i], tab);
    if (tab == NULL)
	{
		ft_freetab_cmd(&tab, i);
		return (NULL);
	}
    return (tab);
}

#include <stdio.h>

int	main(int ac, char **av)
{
	char	**tab;
	char	*splitme;
	int		i;

	i = 0;
	if (ac == 1)
		return (0);
	tab = ft_split_cmd(av[1]);
    if (tab == NULL)
    {
        printf("Error\n");
        return (0);
    }
	while (tab[i] != 0)
	{
		printf("tab[%d]: %s\n", i, tab[i]);
		i++;
	}
    printf("fini\n");
    ft_freetab_cmd(tab, i);
	return (0);
}
