/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfraslin <sfraslin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 18:05:34 by sfraslin          #+#    #+#             */
/*   Updated: 2025/02/11 15:45:52 by sfraslin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stddef.h>

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

char	*ft_strdup_quote(char *str, char *tab)
{
	char	c;
	int		i;

	c = str[0];
	tab = (char *)malloc(sizeof(char) * ft_len_cmd(str, c) + 2);
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

char	*ft_strdup_cmd(char *str, char *tab)
{
	int	i;

	i = 0;
	if (str[i] == 34 || str[i] == 39)
	{
		tab = ft_strdup_quote(&str[i], tab);
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

char	**ft_split_cmd(char *str)
{
	char	**tab;
	int		i;
	int		j;
	int		count;

	i = 0;
	j = 0;
	count = ft_count_cmd(str, 0, 1);
	if (count == 0)
		return (NULL);
	tab = (char **)malloc(sizeof(char *) * (count + 1));
	if (tab == NULL)
		return (NULL);
	while (j < count && str[i])
	{
		tab[j] = ft_sort_cmd(str, tab[j], i);
		i += ft_strlen(tab[j]);
		if (str[i] == 32)
			i++;
		j++;
	}
	tab[j] = 0;
	return (tab);
}

char	*ft_sort_cmd(char *str, char *tab, int i)
{
	while (str[i] && str[i] == 32)
		i++;
	tab = ft_strdup_cmd(&str[i], tab);
	if (tab == NULL)
	{
		ft_freetab_cmd(&tab, i);
		return (NULL);
	}
	return (tab);
}

/*#include <stdio.h>
int	main(int ac, char **av)
{
	char	**tab;
	char	**cmd;
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
		printf("%s\n", tab[i]);
		i++;
	}
	printf("subsplit\n");
	cmd = ft_subsplit(tab);
	i = 0;
	while (cmd[i] != 0)
	{
		printf("%s\n", cmd[i]);
		i++;
	}
    ft_freetab_cmd(cmd, i);
	return (0);
}*/
