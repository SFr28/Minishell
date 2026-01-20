/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sovincen <sovincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:00:10 by sovincen          #+#    #+#             */
/*   Updated: 2025/02/14 11:49:36 by sovincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	len_l;

	i = 0;
	len_l = ft_strlen(little);
	if (len_l == 0)
		return ((char *)big);
	while (big[i] && i < len)
	{
		if (big[i] == little[0])
		{
			if (ft_strncmp(little, &big[i], len_l) == 0 && (i + len_l) <= len)
				return ((char *)&big[i]);
		}
		i++;
	}
	return (NULL);
}
