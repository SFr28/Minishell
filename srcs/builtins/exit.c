/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sovincen <sovincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:20:40 by sovincen          #+#    #+#             */
/*   Updated: 2025/02/27 10:53:36 by sovincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

//Check if the argument is a digit 
static int	check_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i] && ft_is_space(str[i]) != 0)
		i++;
	if (str[i] && (str[i] == '-' || str[i] == '+'))
		i++;
	if (str[i] == '\0' || ft_isdigit(str[i]) == 0)
		return (0);
	while (str[i] && ft_isdigit(str[i]) != 0)
		i++;
	while (str[i])
	{
		if (ft_is_space(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

//Exit the program with the status give as args
//If they are more than 2 args("exit","<status>"), error
//If no status are given, status = value for the last command executed
//(0 if )
//Clear the environment and the history before leving the program
int	ft_exit(char **args, t_env **env_ms, t_data *data)
{
	if (ft_count_args(args) > 2)
	{
		ft_putendl_fd("exit: too many arguments", 2);
		return (1);
	}
	rl_clear_history();
	clear_env(env_ms);
	restore_std(data->saved_stdin, data->saved_stdout);
	if (args[1] == NULL)
	{
		ft_free_cmds(data->cmds_list);
		free(data);
		exit(g_status);
	}
	if (check_digit(args[1]) != 1)
	{
		ft_putendl_fd("exit: numeric argument required", 2);
		g_status = 2;
	}
	else
		g_status = ft_atoi(args[1]);
	ft_free_cmds(data->cmds_list);
	free(data);
	g_status = g_status % 256;
	exit(g_status);
}
