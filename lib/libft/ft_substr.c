/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sovincen <sovincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 17:55:00 by sovincen          #+#    #+#             */
/*   Updated: 2025/02/14 17:43:00 by sovincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	len_s;
	size_t	len_subs;
	char	*subs;

	i = 0;
	len_s = ft_strlen(s);
	len_subs = len_s - start;
	if (start >= len_s)
	{
		subs = ft_calloc(1, sizeof(char));
		return (subs);
	}
	if ((start + len) < len_s)
		len_subs = len;
	subs = malloc((len_subs + 1) * sizeof(char));
	if (subs == NULL)
		return (NULL);
	while (s != NULL && s[i + start] && i < len)
	{
		subs[i] = s[i + start];
		i++;
	}
	subs[i] = '\0';
	return (subs);
}
