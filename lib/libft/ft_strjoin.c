/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sovincen <sovincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 10:32:46 by sovincen          #+#    #+#             */
/*   Updated: 2025/01/23 12:56:17 by sovincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	size_t	len_dest;
	char	*dest;

	len_dest = ft_strlen(s1) + ft_strlen(s2);
	dest = malloc((len_dest + 1) * sizeof(char));
	ft_bzero(dest, (len_dest + 1));
	if (dest == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (i < len_dest && j < ft_strlen(s1))
		dest[i++] = s1[j++];
	j = 0;
	while (i < len_dest && j < ft_strlen(s2))
		dest[i++] = s2[j++];
	dest[i] = '\0';
	return (dest);
}
