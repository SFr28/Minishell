/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   microshell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfraslin <sfraslin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:49:27 by sfraslin          #+#    #+#             */
/*   Updated: 2025/04/14 11:58:29 by sfraslin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "microshell.h"

int	main(int ac, char **av, char *env[])
{
	int	i;
	int	save_fd;

	if (ac == 1)
		return (0);
	save_fd = dup(0);
	i = 0;
	while (av[i] && av[i + 1])
	{
		av = &av[i + 1];
		i = 0;
		while (av[i] && strncmp(av[i], "|", 2) != 0 && strncmp(av[i], ";", 2) != 0)
			i++;
		if (strncmp(av[0], "cd", 3) == 0)
			ft_cd(av, i);
		if (i != 0 && av[i] && strncmp(av[i], "|", 2) == 0)
			child_process(av, env, i, &save_fd);
		if (i != 0 && av[i] && strncmp(av[i], ";", 2) == 0)
			execution(av, env, i, &save_fd);
	}
	close(save_fd);
	return (0);
}

void	child_process(char **av, char *env[], int i, int *save_fd)
{
	int	pid;
	int	pipe_fd[2];

	if (pipe(pipe_fd) == -1)
	{
		ft_errors("error: fatal", NULL);
		exit(1);
	}
	pid = fork();
	if (pid == 0)
	{
		av[i] = NULL;
		close(pipe_fd[0]);
		dup2(pipe_fd[1], 1);
		close(pipe_fd[1]);
		dup2(*save_fd, 0);
		close(*save_fd);
		if (execve(av[0], av, env) == -1)
		{
			ft_errors("error: cannot execute ", av[0]);
			exit(1);
		}
	}
	waitpid(pid, NULL, 0);
	close(pipe_fd[1]);
	close(*save_fd);
	*save_fd = pipe_fd[0];
}

void	execution(char **av, char *env[], int i, int *save_fd)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		av[i] = NULL;
		dup2(*save_fd, 0);
		close(*save_fd);
		if (execve(av[0], av, env) == -1)
		{
			ft_errors("error: cannot execute ", av[0]);
			exit(1);
		}
	}
	waitpid(pid, NULL, 0);
	close(*save_fd);
	*save_fd = dup(0);
}

void	ft_cd(char **av, int i)
{
	if (i != 2)
		ft_errors("error: cd: bad arguments", NULL);
	else if (chdir(av[1]) == -1)
		ft_errors("error: cannot change directory ", av[i + 1]);
}

void	ft_errors(char *s1, char *s2)
{
	int	i;
	
	i = 0;
	while (s1[i])
	{
		write(2, &s1[i], 1);
		i++;
	}
	i = 0;
	if (s2)
	{
		while (s2[i])
		{
			write(2, &s2[i], 1);
			i++;
		}
	}
	write (2, "\n", 1);
}
