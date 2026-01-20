/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sovincen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 14:59:44 by sovincen          #+#    #+#             */
/*   Updated: 2024/11/18 10:30:35 by sovincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_lennbr(long n)
{
	int	len;

	len = 1;
	if (n < 0)
		len++;
	while (n > 9 || - n > 9)
	{
		len++;
		n = n / 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*nbr;
	int		len_nbr;
	int		i;
	long	nb;

	nb = n;
	len_nbr = ft_lennbr(nb);
	i = len_nbr - 1;
	nbr = malloc((len_nbr + 1) * sizeof(char));
	if (nbr == NULL)
		return (NULL);
	if (nb < 0)
	{
		nbr[0] = '-';
		nb = -nb;
	}
	while (nb > 9)
	{
		nbr[i] = nb % 10 + '0';
		nb = nb / 10;
		i--;
	}
	nbr[i] = nb % 10 + '0';
	nbr[len_nbr] = '\0';
	return (nbr);
}
