/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfraslin <sfraslin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 13:40:17 by sovincen          #+#    #+#             */
/*   Updated: 2025/07/04 18:48:52 by sfraslin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "macros.h"

extern int	g_status;

//Wait until all command are executed
int	wait_cmd(t_cmd **cmds_list)
{
	t_cmd	*cmd;
	int		status;

	cmd = *cmds_list;
	while (cmd != NULL)
	{
		if (cmd->pid != 0 && cmd->builtin == 0)
		{
			waitpid(cmd->pid, &status, 0);
			status = WEXITSTATUS(status);
		}
		else
			status = cmd->status;
		cmd = cmd->next;
	}
	return (status);
}

//Restore STDIN and STDOUT thanks to the duplicate we saved at 
//the begining of the execution of the command line
void	restore_std(int saved_stdin, int saved_stdout)
{
	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdin);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdout);
}

//Execute each command of the command line when there is pipe
//Wait all the command and return there exit status
static int	execute_pipe(t_data *data, t_env **env_ms)
{
	int		status;
	t_cmd	*cmd;

	cmd = *(data->cmds_list);
	while (cmd != NULL)
	{
		if (check_for_rm(cmd) == 0)
			cmd->pid = execute_cmd(cmd, env_ms, data);
		cmd = cmd->next;
	}
	status = wait_cmd(data->cmds_list);
	return (status);
}

//Initialise a structure with general info about the command line
//	-A duplicate of STDIN and STDOUT before any changed to save them
//	-The number of command in the chained list
//	-The head of the chained list
static t_data	*init_data(t_cmd **cmds_list)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (data == NULL)
		return (NULL);
	data->saved_stdin = dup(STDIN_FILENO);
	data->saved_stdout = dup(STDOUT_FILENO);
	data->nb_cmd = cmdlist_size(cmds_list);
	data->cmds_list = cmds_list;
	return (data);
}

//Execution of a command line
//	-initialise a structure with general info about the command line
//	-if the command line is only one command => execute_single_cmd
//	-else => execute_pipe
//	-free the list of command, free data, and restore stdin and stdout
void	execution(t_cmd **cmds_list, t_env **env_ms)
{
	t_data	*data;
	int		status;

	status = 0;
	data = init_data(cmds_list);
	if (data == NULL)
	{
		g_status = 1;
		return ;
	}
	if (data->nb_cmd == 1)
	{
		if (check_for_rm(*cmds_list) == 0)
			status = execute_single_cmd(data, env_ms);
	}
	else
		status = execute_pipe(data, env_ms);
	if (g_status != 130)
		g_status = status;
	ft_free_cmds(cmds_list);
	restore_std(data->saved_stdin, data->saved_stdout);
	free(data);
}
