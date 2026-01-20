/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfraslin <sfraslin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 09:57:59 by sfraslin          #+#    #+#             */
/*   Updated: 2025/03/07 10:03:07 by sfraslin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "macros.h"

//Check if the cmd is a builtin or not
static int	ft_is_builtin(t_cmd *temp)
{
	size_t	len;

	if (!temp->args || !temp->args[0])
		return (0);
	len = ft_strlen(temp->args[0]);
	if (ft_strncmp(temp->args[0], "echo", (len + 1)) == 0)
		temp->builtin = FT_ECHO;
	else if (ft_strncmp(temp->args[0], "cd", (len + 1)) == 0)
		temp->builtin = FT_CD;
	else if (ft_strncmp(temp->args[0], "pwd", (len + 1)) == 0)
		temp->builtin = FT_PWD;
	else if (ft_strncmp(temp->args[0], "export", (len + 1)) == 0)
		temp->builtin = FT_EXPORT;
	else if (ft_strncmp(temp->args[0], "unset", (len + 1)) == 0)
		temp->builtin = FT_UNSET;
	else if (ft_strncmp(temp->args[0], "env", (len + 1)) == 0)
		temp->builtin = FT_ENV;
	else if (ft_strncmp(temp->args[0], "exit", (len + 1)) == 0)
		temp->builtin = FT_EXIT;
	else if (ft_strncmp(temp->args[0], "miaou", (len + 1)) == 0)
		temp->builtin = FT_MIAOU;
	if (temp->builtin != 0)
		return (1);
	temp->builtin = 0;
	return (0);
}

//Read first arg in cmd list->args to see if the cmd is a builtin or not
int	ft_find_cmds(t_cmd **cmd, t_env **env)
{
	t_cmd	*temp;
	t_env	*env_temp;

	temp = *cmd;
	env_temp = *env;
	while (temp != NULL)
	{
		if (!temp->args)
		{
			if (temp->fd_in != 0)
				close(temp->fd_in);
			if (temp->fd_out != 1)
				close(temp->fd_out);
			return (-1);
		}
		if (ft_is_builtin(temp) == 0)
			ft_find_path(temp, env_temp);
		if (ft_is_builtin(temp) == 0 && temp->path == NULL)
			temp->path = ft_pre_memcpy(temp->path, temp->args[0]);
		if (temp->path == NULL && temp->builtin == 0)
			return (-1);
		temp = temp->next;
	}
	return (0);
}

//Find cmd's path if it exists
void	ft_find_path(t_cmd *cmd, t_env *temp)
{
	char	**pp;
	int		i;

	i = -1;
	while (temp != NULL && ft_strncmp(temp->name, "PATH", 5) != 0)
		temp = temp->next;
	if (temp == NULL)
		return ;
	pp = ft_split(temp->var, ':');
	if (pp == NULL)
		return ;
	while (pp[++i])
	{
		pp[i] = ft_join_path(pp[i], cmd->args[0]);
		if (pp[i] == NULL)
			return ;
	}
	i = 0;
	while (pp[i] && access(pp[i], X_OK) != 0)
		i++;
	if (pp[i])
		cmd->path = ft_pre_memcpy(cmd->path, pp[i]);
	else
		cmd->path = ft_pre_memcpy(cmd->path, cmd->args[0]);
	ft_freetab_cmd(pp);
}

//Allocate memory to copy a str
char	*ft_pre_memcpy(char *dest, char *src)
{
	int	len;

	len = ft_strlen(src);
	dest = malloc(sizeof(char) * len + 1);
	if (dest == NULL)
		return (NULL);
	dest = ft_memcpy(dest, src, len);
	dest[len] = '\0';
	return (dest);
}

//Write the path found by joining cmd name + path
char	*ft_join_path(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	size_t	len_dest;
	char	*dest;

	len_dest = ft_strlen(s1) + ft_strlen(s2);
	dest = malloc((len_dest + 2) * sizeof(char));
	if (dest == NULL)
		return (NULL);
	ft_bzero(dest, (len_dest + 2));
	i = 0;
	j = 0;
	while (i < len_dest && j < ft_strlen(s1))
		dest[i++] = s1[j++];
	j = 0;
	dest[i++] = '/';
	while (i < (len_dest + 1) && j < ft_strlen(s2))
		dest[i++] = s2[j++];
	dest[i++] = '\0';
	free(s1);
	return (dest);
}
