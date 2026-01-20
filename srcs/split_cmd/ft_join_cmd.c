/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfraslin <sfraslin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 10:59:46 by sfraslin          #+#    #+#             */
/*   Updated: 2025/03/06 11:43:01 by sfraslin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_cmd(char *table, char *str, int start)
{
	char	*temp;
	char	*final;
	int		i;
	int		j;

	j = -1;
	temp = NULL;
	temp = ft_strdup_cmd(&str[start], temp);
	if (temp == NULL)
		return (NULL);
	final = malloc(sizeof(char) * (ft_strlen(table) + ft_strlen(temp) + 1));
	if (final == NULL)
		return (NULL);
	while (table[++j])
		final[j] = table[j];
	i = -1;
	while (temp[++i])
		final[j + i] = temp[i];
	final[j + i] = '\0';
	free(table);
	free(temp);
	return (final);
}
