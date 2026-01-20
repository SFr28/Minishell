# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sfraslin <sfraslin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/18 10:30:20 by sovincen          #+#    #+#              #
#    Updated: 2025/03/06 11:17:05 by sfraslin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
INCLUDES = -I ./includes/ -I ./lib/libft/
NAME = minishell
LIB = -Llib/libft -lft -lreadline
LIBFT = ./lib/libft/libft.a
SRCS_DIR = srcs/
OBJS_DIR = objs/

FILES = main.c \
		environment.c utils_env.c utils_envlst.c env_lsttoarr.c \
		echo.c pwd.c cd.c env.c export.c unset.c exit.c miaou.c \
		ft_split_cmd.c ft_split_utils.c ft_sub_split.c ft_change_var.c ft_join_cmd.c \
		treat_line.c ft_parsing.c token_functions.c build_cmds.c find_cmds.c \
		execute.c execute_cmd.c execute_single_cmd.c error.c \
		redirections.c \
		utils_cmdlist.c utils_builtins.c ft_isspace.c utils_cmds.c utils_sub_split.c \
		signals.c
		
SRCS = $(addprefix $(SRCS_DIR), $(FILES))

OBJS = $(addprefix $(OBJS_DIR), $(FILES:.c=.o))

vpath %.c $(SRCS_DIR) $(SRCS_DIR)builtins $(SRCS_DIR)environment \
$(SRCS_DIR)split_cmd $(SRCS_DIR)parsing  $(SRCS_DIR)redirections \
$(SRCS_DIR)execution $(SRCS_DIR)utils $(SRCS_DIR)signals

all : $(NAME)

$(NAME) : $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) -o $(NAME) $(LIB)

$(OBJS_DIR)%.o : %.c
	mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	
$(LIBFT) :
	make all --no-print-directory -C ./lib/libft

clean :
	rm -rf $(OBJS_DIR)
	make clean --no-print-directory -C ./lib/libft

fclean : clean
	rm -f $(NAME)
	make fclean --no-print-directory -C ./lib/libft

re : fclean all

.PHONY : all clean fclean re
