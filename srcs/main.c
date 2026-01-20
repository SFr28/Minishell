/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfraslin <sfraslin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 10:07:21 by sovincen          #+#    #+#             */
/*   Updated: 2025/07/30 11:02:52 by sfraslin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "macros.h"

int	g_status = 0;

int	main(int argc, char *argv[], char *env[])
{
	char	*line;
	t_env	*env_ms;

	env_ms = NULL;
	init_env(argc, argv, env, &env_ms);
	adjust_shlvl(&env_ms);
	while (1)
	{
		signal(SIGINT, &ft_ctrl_c);
		signal(SIGQUIT, SIG_IGN);
		line = readline("minishell> ");
		if (treat_line(line, &env_ms) == 1)
			break ;
		rl_on_new_line();
	}
	rl_clear_history();
	clear_env(&env_ms);
	return (g_status);
}

