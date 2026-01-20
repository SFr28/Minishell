/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sovincen <sovincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:08:25 by sovincen          #+#    #+#             */
/*   Updated: 2025/02/18 13:28:42 by sovincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Display on the standart output the current working directory
int	ft_pwd(void)
{
	char	*pathname;

	pathname = getcwd(NULL, 0);
	ft_putendl_fd(pathname, 1);
	free(pathname);
	return (0);
}
