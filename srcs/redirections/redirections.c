/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sovincen <sovincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 10:51:07 by sovincen          #+#    #+#             */
/*   Updated: 2025/03/07 09:59:06 by sovincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "macros.h"

extern int	g_status;

static int	init_heredoc(char *limiter)
{
	int		heredoc_fd[2];
	int		len_l;
	char	*line;

	signal(SIGINT, &sig_heredoc);
	if (pipe(heredoc_fd) == -1)
		return (-1);
	len_l = ft_strlen(limiter);
	while (1)
	{
		ft_putstr_fd(">", 1);
		line = get_next_line(0);
		if (line == NULL)
			break ;
		if (ft_strncmp(line, limiter, len_l) == 0 && line[len_l] == '\n')
		{
			free(line);
			break ;
		}
		write(heredoc_fd[1], line, ft_strlen(line));
		free(line);
	}
	close (heredoc_fd[1]);
	return (heredoc_fd[0]);
}

//If the redirection is a heredoc, saved STDIN and restore it after 
//initialise the heredoc, in case the heredoc is interupted by a signal
//(in that case, the signal close STDIN to be able to get out of the heredoc)
static int	handle_heredoc(char *file)
{
	int	fd;
	int	saved_stdin;

	saved_stdin = dup(STDIN_FILENO);
	fd = init_heredoc(file);
	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdin);
	if (fd == -1)
		ft_putendl_fd("heredoc : Failed to initialise", 2);
	return (fd);
}

//Open the infile and the outfile and stock they fd in cmd
int	open_file(char *file, int redir_type)
{
	int	fd;

	fd = -1;
	if (redir_type == HERE_DOC && g_status != 130)
		fd = handle_heredoc(file);
	if (redir_type == REDIR_INPUT)
	{
		fd = open(file, O_RDONLY);
		if (fd == -1)
		{
			perror(file);
			fd = open("/dev/null", O_RDONLY);
			return (fd);
		}
	}
	if (ft_strncmp(file, "<", 1) != 0 && ft_strncmp(file, ">", 1) != 0)
	{
		if (redir_type == REDIR_OUTPUT)
			fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (redir_type == REDIR_OUTPUT_APPEND)
			fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	}
	return (fd);
}
