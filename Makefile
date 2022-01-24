# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qestefan <qestefan@student.21-school.ru    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/21 21:25:47 by qestefan          #+#    #+#              #
#    Updated: 2022/01/24 14:05:29 by qestefan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLAGS = -Wall -Wextra -Werror

NAME_PROJECT = pipex
LIB_DIR = ./libft/
LIB_NAME =	libft/libft.a
LIB_HEADER = libft
LIBFT = libft.a
CC = gcc
HEADER = includes
OBJS = $(SRCS:.c=.o)
DIR = ./source/
SRCS = $(DIR)pipex.c $(DIR)utils.c
AR = ar rc

.c.o:
	$(CC) $(FLAGS) -c -I$(HEADER) -I$(LIB_HEADER) $< -o $(<:.c=.o)

all: $(LIBFT) $(NAME_PROJECT)

$(NAME): $(OBJS) $(HEADER)
	$(MAKE) -C $(LIB_DIR)
	$(CC) $(FLAGS) $(OBJS) $(LIB_NAME) -o $(NAME_PROJECT)

bonus : $(LIBFT) $(NAME_PROJECT)
$(LIBFT):
		@$(MAKE) -C $(LIB_DIR)
$(NAME_PROJECT): $(OBJS)
		$(CC) $(FLAGS) -I$(HEADER) $(OBJS) -L. $(LIB_NAME) -o $(NAME_PROJECT)

clean:
	make clean -C $(LIB_DIR)
	rm -rf $(OBJS)

fclean: clean
	make fclean -C $(LIB_DIR)
	rm -rf $(NAME_PROJECT)
re: fclean all

norm:
	norminette source/*.c includes/*.h

.PHONY: all clean fclean re code bonus norm
