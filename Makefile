# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/11 09:10:49 by idakhlao          #+#    #+#              #
#    Updated: 2024/05/21 14:39:07 by idakhlao         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
BONUS = pipex_bonus

SRCS = src/main.c src/utils.c
SRCS_BONUS = src/pipex_bonus.c src/utils_bonus.c
OBJS = ${SRCS:.c=.o}
OBJS_BONUS = ${SRCS_BONUS:.c=.o}
CFLAGS = -Wall -Wextra -Werror -g3
PRINTF = ./printf/libftprintf.a
LIBFT = ./libft/libft.a
CC = cc
RM = rm -f

all : $(NAME) 

.c.o:
	cc $(CFLAGS) -c -o $@ $< 

$(NAME): start $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(PRINTF) $(LIBFT)

bonus: start $(OBJS_BONUS)
	$(CC) $(CFLAGS) $(OBJS_BONUS) -o $(BONUS) $(PRINTF) $(LIBFT)

start :
	make -C printf all
	make -C libft all

clean :
	${RM} ${OBJS}
	make -C printf clean
	make -C libft clean

fclean : clean
	${RM} ${NAME}
	make -C printf fclean
	make -C libft fclean

re : fclean all

.PHONY = make clean fclean re