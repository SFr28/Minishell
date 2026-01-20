/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lsttoarr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sovincen <sovincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 17:53:29 by sovincen          #+#    #+#             */
/*   Updated: 2025/02/27 14:50:20 by sovincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Join to str with a symbol '=' between them
static char	*ft_strjoin_env(char const *s1, char const *s2)
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
	dest[i++] = '=';
	j = 0;
	while (i <= len_dest && j < ft_strlen(s2))
		dest[i++] = s2[j++];
	dest[i] = '\0';
	return (dest);
}

//Construct and return the environment variable as an array based 
//on the environment chained list 
char	**env_lsttoarr(t_env **env_lst)
{
	t_env	*var;
	char	**env_arr;
	int		len_env_lst;
	int		i;

	var = *env_lst;
	len_env_lst = env_size(env_lst);
	env_arr = malloc(sizeof(char *) * (len_env_lst + 1));
	if (env_arr == NULL)
		return (NULL);
	i = 0;
	while (var != NULL)
	{
		env_arr[i] = ft_strjoin_env(var->name, var->var);
		i++;
		var = var->next;
	}
	env_arr[len_env_lst] = NULL;
	return (env_arr);
}
