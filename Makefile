# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qestefan <qestefan@student.21-school.ru    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/21 21:25:47 by qestefan          #+#    #+#              #
#    Updated: 2022/01/21 21:35:27 by qestefan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	= pipex.a
PROG	= pipex

SRCS 	= pipex.c utils.c
OBJS 	= ${SRCS:.c=.o}
MAIN	= pipex.c

SRCS_B	= pipex_bonus.c utils.c utils_bonus.c
OBJS_B	= ${SRCS_B:.c=.o}
MAIN_B	= pipex_bonus.c

HEADER	= -I./includes/

CC 		= gcc
CFLAGS 	= -Wall -Wextra -Werror -g

.c.o:		%.o : %.c
					@gcc ${CFLAGS} ${HEADER} -c $< -o $(<:.c=.o)

$(NAME):	${OBJS}
					@make re -C ./libft
					@cp libft/libft.a ./$(NAME)
					@ar -rcs ${NAME} ${OBJS}
					@$(CC) $(NAME) ${MAIN} -o ${PROG}

all: 		${NAME}

bonus:		${OBJS_B}
					@make re -C ./libft
					@cp libft/libft.a ./$(NAME)
					@ar -rcs ${NAME} ${OBJS_B}
					@$(CC) $(NAME) ${MAIN_B} -o ${PROG}

clean:
					@make clean -C ./libft
					@rm -f ${OBJS} ${OBJS_B}

fclean: 	clean
					@make fclean -C ./libft
					@rm -f $(NAME)
					@rm -f ${PROG}

re:			fclean all

.PHONY: all clean fclean re bonus party
