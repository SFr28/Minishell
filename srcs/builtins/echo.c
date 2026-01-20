/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sovincen <sovincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 10:41:03 by sovincen          #+#    #+#             */
/*   Updated: 2025/02/25 17:11:27 by sovincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_flag(char *arg)
{
	size_t	i;

	i = 0;
	if (arg[i] != '-')
		return (0);
	i++;
	while (arg != NULL && arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

//Write the text in args in the standart output
//If the first argument is the flag -n : don't output the trailing newline
//If they are more than 1 arg to write, write one space between them
int	ft_echo(char **args)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	while (args[i] && check_flag(args[i]) == 1)
	{
		flag = 1;
		i++;
	}
	while (args[i] != NULL)
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1] != NULL)
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (flag == 0)
		ft_putchar_fd('\n', 1);
	return (0);
}
