/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sub_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfraslin <sfraslin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 12:07:21 by sfraslin          #+#    #+#             */
/*   Updated: 2025/02/11 15:44:42 by sfraslin         ###   ########.fr       */
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

//enlever les ' " et separer | < > des mots
char    **ft_subsplit(char **tab)
{
    char    **cmd;
    int i;
    int j;

    cmd = (char **)malloc(sizeof(char *) * (ft_subcount(tab) + 1));
    if (cmd == NULL)
        return (NULL);
    i = 0;
    j = 0;
    while (tab[i] != 0)
    {
        cmd[j] = ft_strcpy_cmd(tab[i], cmd[j]);
        if ((tab[i][0] == '|' || tab[i][0] == '>' || tab[i][0] == '<') && tab[i][1] != '\0')
        {
            j++;
            cmd[j] = ft_strcpy_cmd(&tab[i][1], cmd[j]);
        }
        j++;
        i++;
    }
    ft_freetab_cmd(tab, i);
    return (cmd);
}

int ft_subcount(char **tab)
{
    int i;
    int count;

    i = 0;
    count = 0;
    while (tab[i] != 0)
    {
        if ((tab[i][0] == '|' || tab[i][0] == '>' || tab[i][0] == '<') && tab[i][1] != '\0')
            count++;
        count++;
        i++;
    }
    return (count);
}

char    *ft_strcpy_cmd(char *tab, char *cmd)
{
    int i;

    i = 0;
    if (tab[0] == '|' || tab[0] == '>' || tab[0] == '<') //attention: ca ne prend en compte que le cas ou le caractere est en premier, pas en dernier
    {
        cmd = ft_strcpy_other(tab, cmd);
        return (cmd);
    }
    if (tab[0] == '\'' || tab[0] == '\"')
    {
        cmd = ft_strcpy_quote(tab, cmd);
        return (cmd);
    }
    cmd = malloc(sizeof(char) * (ft_strlen(tab) + 1));
    if (cmd == NULL)
        return (NULL);
    while (tab[i])
    {
        cmd[i] = tab[i];
        i++;
    }
    cmd[i] = '\0';
    return (cmd);
}

char    *ft_strcpy_other(char *tab, char *cmd)
{
    cmd = malloc(sizeof(char) * 2);
    if (cmd == NULL)
        return (NULL);
    cmd[0] = tab[0];
    cmd[1] = '\0';
    return (cmd);
}

char    *ft_strcpy_quote(char *tab, char *cmd)
{
    int i;
    int j;

    i = 1;
    j = 0;
    cmd = malloc(sizeof(char) * (ft_strlen(tab) - 1));
    if (cmd == NULL)
        return (NULL);
    while (tab[i] != '\'' && tab[i] != '\"')
    {
        cmd[j] = tab[i];
        i++;
        j++;
    }
    cmd[j] = '\0';
    return (cmd);
}
