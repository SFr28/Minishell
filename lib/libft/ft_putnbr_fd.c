/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sovincen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 17:09:58 by sovincen          #+#    #+#             */
/*   Updated: 2024/11/18 12:01:57 by sovincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putnbr_fd(int n, int fd)
{
	char	nb_print;

	if (fd > 0)
	{
		if (n == -2147483648)
			write(fd, "-2147483648", 11);
		else
		{
			if (n < 0)
			{
				write(fd, "-", 1);
				n = -n;
			}
			if (n > 9)
				ft_putnbr_fd(n / 10, fd);
			nb_print = n % 10 + '0';
			write(fd, &nb_print, 1);
		}
	}
}
