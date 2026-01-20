/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sovincen <sovincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 10:41:11 by sovincen          #+#    #+#             */
/*   Updated: 2025/02/25 16:00:54 by sovincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Return the len of the variable name, meaning the lenght of the variable until
//a '=' is found
int	ft_strlen_name(char *env_var)
{
	int	len;

	len = 0;
	while (env_var != NULL && env_var[len] && env_var[len] != '=')
		len++;
	return (len);
}

//Duplicate the n first character of a string
static char	*ft_strndup(const char *s, int n)
{
	char	*dest;
	int		i;

	i = 0;
	if (n == 0)
		return (NULL);
	dest = malloc((n + 1) * sizeof(char));
	if (dest == NULL)
		return (NULL);
	while (s[i] && i < n)
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

//Free a double array
void	free_split(char **s)
{
	int	i;

	i = 0;
	while (s != NULL && s[i] != NULL)
	{
		free(s[i]);
		i++;
	}
	free(s);
}

//Split one environment variable based on the first '=' found
//The first element is the name
//The second element is the value
char	**split_env(char *var)
{
	int		len_element;
	int		i;
	char	**split;

	i = 0;
	split = malloc(3 * sizeof(char *));
	if (split == NULL)
		return (NULL);
	while (i < 2)
	{
		if (i == 0)
			len_element = ft_strlen_name(var);
		else
			len_element = ft_strlen(var);
		split[i] = ft_strndup(var, len_element);
		if (split[i] == NULL && var[0] != '\0')
		{
			free_split(split);
			return (NULL);
		}
		var += len_element + 1;
		i++;
	}
	split[i] = NULL;
	return (split);
}
