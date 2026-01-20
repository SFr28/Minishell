/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sovincen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 17:47:46 by sovincen          #+#    #+#             */
/*   Updated: 2024/11/13 15:57:40 by sovincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*ptr_s1;
	const unsigned char	*ptr_s2;

	ptr_s1 = s1;
	ptr_s2 = s2;
	if (n == 0)
		return (0);
	while (n--)
	{
		if (*ptr_s1 != *ptr_s2)
			return ((int)(*ptr_s1 - *ptr_s2));
		ptr_s1++;
		ptr_s2++;
	}
	return (0);
}
