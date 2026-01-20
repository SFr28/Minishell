/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sovincen <sovincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 15:03:44 by sovincen          #+#    #+#             */
/*   Updated: 2025/02/14 16:56:23 by sovincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//Concatenate dest and src (with '\0' at the end)
//size : represent the memory size we want to allocate to the concatenate
//strings
size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	len_dst;
	size_t	available_space;

	i = 0;
	len_dst = ft_strlen(dst);
	available_space = size - len_dst - 1;
	if (size <= len_dst)
		return (size + ft_strlen(src));
	while (src != NULL && src[i] != '\0' && i < (available_space))
	{
		dst[len_dst + i] = src[i];
		i++;
	}
	dst[len_dst + i] = '\0';
	return (ft_strlen(src) + len_dst);
}
