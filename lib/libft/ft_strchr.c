/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sovincen <sovincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 11:28:11 by sovincen          #+#    #+#             */
/*   Updated: 2025/02/14 16:46:52 by sovincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//Return the first instance of c in the string s or NULL if c does not occur
char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	c = c % 256;
	while (s != NULL && s[i])
	{
		if (s[i] == c)
			return ((char *)&s[i]);
		i++;
	}
	if (s != NULL && s[i] == '\0' && c == '\0')
		return ((char *)&s[i]);
	return (NULL);
}
