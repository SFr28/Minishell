/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sovincen <sovincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 17:51:13 by sovincen          #+#    #+#             */
/*   Updated: 2025/02/14 16:45:40 by sovincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s);

char	*ft_strdup(const char *s)
{
	char	*dest;
	size_t	i;
	size_t	len_s;

	i = 0;
	len_s = ft_strlen(s);
	dest = malloc(len_s * sizeof(char) + 1);
	if (dest == NULL)
		return (0);
	while (s != NULL && s[i])
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
