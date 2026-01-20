/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sovincen <sovincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:22:02 by sovincen          #+#    #+#             */
/*   Updated: 2025/02/14 16:47:46 by sovincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//Return the number of elements in the string s
static size_t	ft_countelement(char const *s, char c)
{
	size_t	nb_element;
	size_t	i;

	nb_element = 0;
	i = 0;
	while (s != NULL && s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			nb_element++;
		i++;
	}
	return (nb_element);
}

//Return the lenght of one elements of the string s
size_t	ft_strlen_split(const char *s, char c)
{
	size_t	len;

	len = 0;
	while (s != NULL && s[len] && s[len] != c)
		len++;
	return (len);
}

//Return the copy of a string
static char	*ft_strndup(const char *s, size_t n)
{
	char	*dest;
	size_t	i;

	i = 0;
	dest = malloc((n + 1) * sizeof(char));
	if (dest == NULL)
		return (NULL);
	while (s != NULL && s[i] && i < n)
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

//Free all the string already allocated if an error occurs in strndup
static void	ft_free_split(char **s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		free(s[i]);
		i++;
	}
	free(s);
}

//Return an array of strings obtained by splitting s by c 
char	**ft_split(char const *s, char c)
{
	size_t	nb_element;
	size_t	len_element;
	size_t	i;
	char	**s_split;

	i = 0;
	nb_element = ft_countelement(s, c);
	s_split = malloc((nb_element + 1) * sizeof(char *));
	if (s_split == NULL)
		return (NULL);
	while (i < nb_element)
	{
		while (*s == c)
			s++;
		len_element = ft_strlen_split(s, c);
		s_split[i] = ft_strndup(s, len_element);
		if (s_split[i] == NULL)
			return (ft_free_split(s_split, i), NULL);
		s += len_element;
		i++;
	}
	s_split[i] = NULL;
	return (s_split);
}
