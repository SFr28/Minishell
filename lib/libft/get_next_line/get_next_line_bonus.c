/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sovincen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 11:49:57 by sovincen          #+#    #+#             */
/*   Updated: 2024/12/06 11:09:25 by sovincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

//Main function
//Return the line found and save the part read after the newline if it exist
char	*get_next_line(int fd)
{
	static char	save[1024][BUFFER_SIZE];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	if (save[fd][0])
		line = ft_strjoin(line, save[fd]);
	line = ft_read_line(fd, line);
	if (line == NULL)
		return (NULL);
	ft_get_save(line, save[fd]);
	line = ft_construct_line(line);
	return (line);
}

//Read the file until a newline is found or the end of file is found
char	*ft_read_line(int fd, char *line)
{
	char	*buffer;
	int		nb_read;
	int		i;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buffer == NULL)
		return (NULL);
	while ((!line || ft_find_newline(line) == 0))
	{
		i = 0;
		while (i < BUFFER_SIZE + 1)
			buffer[i++] = '\0';
		nb_read = read(fd, buffer, BUFFER_SIZE);
		if (nb_read <= 0)
		{
			if (nb_read == 0 && line != NULL)
				break ;
			free(buffer);
			return (NULL);
		}
		line = ft_strjoin(line, buffer);
	}
	free(buffer);
	return (line);
}

//Make the line 
char	*ft_construct_line(char *line_read)
{
	char	*line;
	int		len_line;
	int		i;

	len_line = ft_strlen_line(line_read);
	line = malloc(sizeof(char) * (len_line + 1));
	if (line == NULL)
		return (NULL);
	i = 0;
	while (i < len_line)
	{
		line[i] = line_read[i];
		i++;
	}
	free(line_read);
	line[len_line] = '\0';
	return (line);
}

//Save the character read but after a '\n' 
void	ft_get_save(char *line, char *save)
{
	int		i;
	int		j;
	int		len_line;

	i = 0;
	len_line = ft_strlen_line(line);
	while (i < BUFFER_SIZE)
		save[i++] = '\0';
	i = 0;
	while (i < len_line)
		i++;
	j = 0;
	while (j < BUFFER_SIZE && line[i] != '\0')
		save[j++] = line[i++];
	save[j] = '\0';
}
