/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_single_cmd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sovincen <sovincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 10:59:17 by sovincen          #+#    #+#             */
/*   Updated: 2025/03/06 15:16:25 by sovincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "macros.h"

extern int	g_status;

//Redirect the execution of the command to the correct builtin 
//based on the type of builtin identified during parsing
//Cd, Export, Unset and Exit only work if they are a single command
int	execute_builtins(t_cmd *cmd, t_env **env_ms, t_data *data)
{
	int	status;

	status = 0;
	if (cmd->builtin == FT_ECHO)
		status = ft_echo(cmd->args);
	else if (cmd->builtin == FT_CD && data->nb_cmd == 1)
		status = ft_cd(cmd->args, env_ms);
	else if (cmd->builtin == FT_PWD)
		status = ft_pwd();
	else if (cmd->builtin == FT_EXPORT && data->nb_cmd == 1)
		status = ft_export(cmd->args, env_ms);
	else if (cmd->builtin == FT_UNSET && data->nb_cmd == 1)
		status = ft_unset(cmd->args, env_ms);
	else if (cmd->builtin == FT_ENV)
		status = ft_env(cmd->args, env_ms);
	else if (cmd->builtin == FT_EXIT && data->nb_cmd == 1)
		status = ft_exit(cmd->args, env_ms, data);
	else if (cmd->builtin == FT_MIAOU)
		status = ft_miaou();
	return (status);
}

//Check if there is an input redirection
//If it's the case, duplicate fd_in in STDIN
void	set_input(t_cmd *cmd)
{
	if (cmd->fd_in != STDIN_FILENO)
	{
		dup2(cmd->fd_in, STDIN_FILENO);
		close(cmd->fd_in);
	}
}

//Parent process of a single command
//	-Wait the child and get is status
//	-If they're is an output redirection, close the fd_out in the parent
static int	parent_process_single(t_cmd *cmd)
{
	int	status;

	signal(SIGINT, &sig_child);
	waitpid(cmd->pid, &status, 0);
	status = WEXITSTATUS(status);
	if (cmd->fd_out != STDOUT_FILENO)
		close(cmd->fd_out);
	return (status);
}

//Child process of a single command
//Check if there is a redirection of the output
//Reform an array with the environment to pass it to execve
//Execute with execve, if the execution does not work 
//exit the child with the appropriate exit status
static void	child_process_single(t_cmd *cmd, t_env **env_ms, t_data *data)
{
	char	**env_arr;

	if (cmd->fd_out != STDOUT_FILENO)
	{
		dup2(cmd->fd_out, STDOUT_FILENO);
		close(cmd->fd_out);
	}
	env_arr = env_lsttoarr(env_ms);
	close(data->saved_stdin);
	close(data->saved_stdout);
	if (execve(cmd->path, cmd->args, env_arr) == -1)
	{
		if (access(cmd->path, F_OK) == 0)
			g_status = error_execute(cmd, env_ms, env_arr, 126);
		else
			g_status = error_execute(cmd, env_ms, env_arr, 127);
		ft_free_cmds(data->cmds_list);
		free(data);
		rl_clear_history();
		exit(g_status);
	}
}

//Execution when there is no pipe
//Set the input of the command (check for an input redirection)
//If the command is a builtin, execute it in the parent
//Else create a child to execute the command and wait this child
int	execute_single_cmd(t_data *data, t_env **env_ms)
{
	int		status;
	int		pid;
	t_cmd	*cmd;

	cmd = *(data->cmds_list);
	set_input(cmd);
	if (cmd->builtin != 0)
	{
		if (cmd->fd_out != STDOUT_FILENO)
		{
			dup2(cmd->fd_out, STDOUT_FILENO);
			close(cmd->fd_out);
		}
		status = execute_builtins(cmd, env_ms, data);
		return (status);
	}
	pid = fork();
	if (pid == -1)
		error_exit("fork error");
	if (pid == 0)
		child_process_single(cmd, env_ms, data);
	status = parent_process_single(cmd);
	return (status);
}
