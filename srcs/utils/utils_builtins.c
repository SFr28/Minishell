/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sovincen <sovincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 10:37:24 by sovincen          #+#    #+#             */
/*   Updated: 2025/02/27 10:39:39 by sovincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Count the number of arg in an array
int	ft_count_args(char **args)
{
	int	i;

	i = 0;
	while (args && args[i] != NULL)
		i++;
	return (i);
}
