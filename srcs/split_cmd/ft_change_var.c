/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_change_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfraslin <sfraslin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:36:08 by sfraslin          #+#    #+#             */
/*   Updated: 2025/03/07 13:40:16 by sfraslin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

//Replace variable called by $ by its value if it exists
//Used when there are no quotes
static char	*change_no_quote(char *t, char *cmd, char *var, int len)
{
	int	i;
	int	j;
	int	var_len;

	i = -1;
	j = -1;
	var_len = ft_strlen(var);
	cmd = malloc(sizeof(char) * (ft_strlen(t) - len + var_len + 1));
	if (cmd == NULL)
		return (NULL);
	while (t && t[++i] != '$')
		cmd[i] = t[i];
	while (var && var[++j])
		cmd[i + j] = var[j];
	while (t[i + len + 1])
	{
		cmd[i + j] = t[i + len + 1];
		i++;
	}
	if (var_len == 0)
		cmd[0] = '\0';
	else
		cmd[i + j] = '\0';
	return (cmd);
}

//Replace variable called by $ by its value if it exists
//Used when there are doubles quotes
static char	*change_double(char *t, char *cmd, char *var, int len)
{
	int	i;
	int	j;
	int	var_len;

	i = -1;
	j = -1;
	var_len = ft_strlen(var);
	cmd = malloc(sizeof(char) * (ft_strlen(t) - len + var_len + 1));
	if (cmd == NULL)
		return (NULL);
	while (t && t[++i] != '$')
		cmd[i] = t[i];
	while (var && var[++j])
		cmd[i + j] = var[j];
	if (var_len == 0)
		j++;
	while (t[i + len + 1] && t[i + len + 1] != '\"')
	{
		cmd[i + j] = t[i + len + 1];
		i++;
	}
	cmd[i + j] = '\"';
	cmd[i + j + 1] = '\0';
	return (cmd);
}

//Read the line to see which function to call (quotes or no quotes)
static char	*which_change(char *t, char *cmd, char *var, int len)
{
	int		i;

	i = 0;
	while (t && t[i] != '$')
		i++;
	if (t[i + 1] == '?')
	{
		var = ft_itoa(g_status);
		len = 1;
	}
	if (t[0] != '\'' && t[0] != '\"')
		cmd = change_no_quote(t, cmd, var, len);
	else if (t[0] == '\'')
	{
		cmd = ft_pre_memcpy(cmd, &t[1]);
		cmd[ft_strlen(cmd) - 1] = '\0';
	}
	else if (t[0] == '\"')
		cmd = change_double(t, cmd, var, len);
	if (cmd == NULL)
		return (NULL);
	if (t[i + 1] == '?')
		free(var);
	return (cmd);
}

//Check if $ sign appears int cmd line
int	check_dollar(char *table)
{
	int	i;

	i = 0;
	while (table && table[i])
	{
		if (table[i] == '$' && table[i + 1] && ft_isalpha(table[i + 1]) != 0)
			return (i);
		i++;
	}
	return (-1);
}

//Replace variable called by $ by its env value if it exists
//echo "'$HOME'" => '/home/sfraslin'
//echo "$HOME" && echo $HOME => /home/sfraslin
//echo '$HOME' => $HOME
//echo "$truc" && echo $truc => nothing
//echo '$truc' => $truc
//echo "'$truc'" => ''
char	*ft_change_var(char *t, char *cmd, t_env **env, int x)
{
	t_env	*temp;
	int		i;
	int		j;

	temp = *env;
	i = check_dollar(t) + 1;
	j = i;
	while (t[i] && t[i] != '\"' && t[i] != '\'' && t[i] != ' ' && t[i] != '$')
		i++;
	while (temp && ft_strncmp(&t[j], temp->name, ft_strlen(temp->name)) != 0)
		temp = temp->next;
	if (temp && (int)ft_strlen(temp->name) != (i - j))
		temp = NULL;
	if (temp == NULL)
		cmd = which_change(t, cmd, NULL, (i - j));
	else
		cmd = which_change(t, cmd, temp->var, (i - j));
	if (cmd && cmd[0] == 0)
	{
		free(cmd);
		cmd = NULL;
	}
	if (x == 1)
		free(t);
	return (cmd);
}
