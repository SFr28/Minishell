/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sovincen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 15:45:11 by sovincen          #+#    #+#             */
/*   Updated: 2024/11/14 16:07:49 by sovincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*dest;
	size_t			len_s;

	i = 0;
	len_s = ft_strlen(s);
	dest = malloc((len_s + 1) * sizeof(char));
	if (dest == NULL)
		return (NULL);
	while (len_s)
	{
		dest[i] = (*f)(i, s[i]);
		i++;
		len_s--;
	}
	dest[i] = '\0';
	return (dest);
}
