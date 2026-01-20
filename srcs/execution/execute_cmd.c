/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sovincen <sovincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 13:06:00 by sovincen          #+#    #+#             */
/*   Updated: 2025/03/06 14:32:49 by sovincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "macros.h"

extern int	g_status;

//Get ready for the next command
//	-If it's not a builtin close the writting side of the pipe
//	-Else, restore STDOUT
//	-If it's not the last command, duplicate the reading side of the pipe
//	 in STDIN
//	-Else (if it's not a builtin), close the reading side of the pipe
//	 (unecessary)
static void	parent_process(t_cmd *cmd, int *p_fd, t_data *data)
{
	signal(SIGINT, &sig_child);
	if (cmd->builtin == 0)
		close(p_fd[1]);
	else
		dup2(data->saved_stdout, STDOUT_FILENO);
	if (cmd && cmd->next != NULL)
	{
		dup2(p_fd[0], STDIN_FILENO);
		close(p_fd[0]);
	}
	else if (cmd->builtin == 0)
		close(p_fd[0]);
	if (cmd->fd_out != STDOUT_FILENO)
		close(cmd->fd_out);
}

//Set the output of the command for commmand in child process
//	-Close the reading side of the pipe (p_fd[0])
//	-if it's the last command dup STDOUT in outfile
//	-else dup STDOUT in writing side of the pipe
static void	set_cmdout(t_cmd *cmd, int *p_fd)
{
	close(p_fd[0]);
	if (cmd->fd_out != STDOUT_FILENO)
	{
		dup2(cmd->fd_out, STDOUT_FILENO);
		close(cmd->fd_out);
	}
	else if (cmd->next != NULL)
		dup2(p_fd[1], STDOUT_FILENO);
	close(p_fd[1]);
}

//Set the output of the command for a builtin (in the parent process)
//Check if there is an output redirection
//	-If there is, duplicate fd_out in STDOUT and close the writting side
//	 of the pipe (not necessary)
//	-Else if it's not the last command, duplicate the writting side 
//	 of the pipe to STDOUT
static void	set_cmdout_builtin(t_cmd *cmd, int *p_fd)
{
	if (cmd->fd_out != STDOUT_FILENO)
	{
		dup2(cmd->fd_out, STDOUT_FILENO);
		close(cmd->fd_out);
		close(p_fd[1]);
	}
	else if (cmd->next != NULL)
	{
		dup2(p_fd[1], STDOUT_FILENO);
		close(p_fd[1]);
	}
}

//Child process
//	-Set the output
//	-Close the duplicate of STDIN and STDOUT which are not necessary here
//	-Reform the environment as an array to pass to execve
//	-execute the command
//	-if -1 return : means execve failed
//		-Free all (env, cmds_list, data)
//		-Exit the child with the appropriate exit status
static void	child_process(t_cmd *cmd, t_env **env_ms, int *p_fd, t_data *data)
{
	char	**env_arr;

	set_cmdout(cmd, p_fd);
	close(data->saved_stdin);
	close(data->saved_stdout);
	env_arr = env_lsttoarr(env_ms);
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

//Execute one command
//	- Initialise a pipe : allow the communication between process
//	- Set input (Check for an input redirection)
//	- Check if the command is a builtin
//		-Set the output for builtin command
//		-execute the builtins in the parent and get is status exit
//	- Else, make a new child (fork)
//	- if pid = 0 : we are in the child process
//	- in the parent, get ready for the next command
int	execute_cmd(t_cmd *cmd, t_env **env_ms, t_data *data)
{
	int		p_fd[2];
	pid_t	pid;

	pid = 0;
	if (pipe(p_fd) == -1)
		error_exit("pipe error");
	set_input(cmd);
	if (cmd->builtin != 0)
	{
		set_cmdout_builtin(cmd, p_fd);
		cmd->status = execute_builtins(cmd, env_ms, data);
		pid = 0;
	}
	else
	{
		pid = fork();
		if (pid == -1)
			error_exit("fork error");
		if (pid == 0)
			child_process(cmd, env_ms, p_fd, data);
		signal(SIGINT, &ft_ctrl_c);
	}
	parent_process(cmd, p_fd, data);
	return (pid);
}
