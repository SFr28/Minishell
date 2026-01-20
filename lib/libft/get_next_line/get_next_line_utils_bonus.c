/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sovincen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:54:12 by sovincen          #+#    #+#             */
/*   Updated: 2024/12/06 11:12:01 by sovincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strjoin(char *s1, char *s2)
{
	int		len_s1;
	int		len_s2;
	char	*line;
	int		i;
	int		j;

	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	line = malloc(sizeof(char) * (len_s1 + len_s2 + 1));
	if (line == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s1 != NULL && s1[j] != '\0')
		line[i++] = s1[j++];
	j = 0;
	while (s2 != NULL && s2[j] != '\0')
		line[i++] = s2[j++];
	line[i] = '\0';
	if (s1 != NULL)
		free(s1);
	return (line);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i])
		i++;
	return (i);
}

int	ft_strlen_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0' && line[i] != '\n')
		i++;
	if (line[i] == '\n')
		i++;
	return (i);
}

int	ft_find_newline(char *line)
{
	int	i;

	if (line == NULL)
		return (0);
	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}
