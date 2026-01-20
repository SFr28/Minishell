/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sovincen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 18:23:50 by sovincen          #+#    #+#             */
/*   Updated: 2024/12/06 11:10:06 by sovincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# include <unistd.h>
# include <stdlib.h>

char	*get_next_line(int fd);
char	*ft_read_line(int fd, char *line);
char	*ft_construct_line(char *line_read);
void	ft_get_save(char *line, char *save);
char	*ft_strjoin(char *s1, char *s2);
int		ft_strlen(char *str);
int		ft_strlen_line(char *line);
int		ft_find_newline(char *line);

#endif
