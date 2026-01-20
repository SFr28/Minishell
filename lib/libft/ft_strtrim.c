/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sovincen <sovincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:03:51 by sovincen          #+#    #+#             */
/*   Updated: 2025/02/14 16:59:12 by sovincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	ft_incharset(const char c, const char *set)
{
	unsigned int	i;

	i = 0;
	while (set != NULL && set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

static size_t	ft_strlen_dest(const char *s, const char *set)
{
	size_t	len_dest;
	size_t	len_s;
	size_t	i;

	i = 0;
	len_s = ft_strlen(s);
	len_dest = len_s;
	while (ft_incharset(s[i], set) == 1)
	{
		len_dest--;
		i++;
	}
	if (i == len_s)
		return (0);
	i = len_s - 1;
	while (ft_incharset(s[i], set) == 1)
	{
		len_dest--;
		i--;
	}
	return (len_dest);
}

static char	*ft_trim(char const *s1, char const *set, char *dest, size_t len_d)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (ft_incharset(s1[i], set) == 1)
		i++;
	while (j < len_d)
	{
		dest[j] = s1[i];
		i++;
		j++;
	}
	dest[j] = '\0';
	return (dest);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	len_dest;
	char	*dest;

	len_dest = ft_strlen_dest(s1, set);
	if (len_dest == 0)
	{
		dest = ft_calloc(1, 1);
		return (dest);
	}
	dest = malloc((len_dest + 1) * sizeof(char));
	if (dest == NULL)
		return (NULL);
	dest = ft_trim(s1, set, dest, len_dest);
	return (dest);
}
