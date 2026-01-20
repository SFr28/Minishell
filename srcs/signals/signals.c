/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfraslin <sfraslin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:45:59 by sfraslin          #+#    #+#             */
/*   Updated: 2025/07/07 17:26:01 by sfraslin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

//status exit : 128 + signal number
//new prompt line ; exit status : 130
void	ft_ctrl_c(int signum)
{
	if (signum == SIGINT)
	{
		g_status = 130;
		ft_putchar_fd('\n', 2);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	sig_child(int signum)
{
	if (signum == SIGINT)
	{
		g_status = 130;
		ft_putchar_fd('\n', 2);
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

void	sig_heredoc(int signum)
{
	if (signum == SIGINT)
	{
		g_status = 130;
		close(STDIN_FILENO);
		ft_putchar_fd('\n', 2);
	}
}
