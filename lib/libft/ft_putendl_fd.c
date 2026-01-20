/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sovincen <sovincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:48:51 by sovincen          #+#    #+#             */
/*   Updated: 2025/02/13 11:57:16 by sovincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	unsigned int	len;

	len = 0;
	if (fd > 0)
	{
		while (s != NULL && s[len])
			len++;
		write(fd, s, len);
		write(fd, "\n", 1);
	}
}
