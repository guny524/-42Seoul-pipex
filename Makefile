# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/11 16:17:45 by min-jo            #+#    #+#              #
#    Updated: 2022/03/22 21:14:42 by min-jo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	pipex
SRC			=	pipex.c perrors.c io_perrors.c string.c split.c quote.c quote_counter_state.c
BDRC		=
OBJ			=	$(SRC:.c=.o)
BOBJ		=	$(BSRC:.c=.o)
CFLAGS		+=	-Wall -Wextra -Werror
# CPPFLAGS	=

all:		$(NAME)

# %.o:		%.c
# 	$(CC) $(CFLAGS) $(CPPFLAGS) $< -c -o $@

$(NAME):	$(OBJ)
	$(CC) $(CFLAGS) $(CPPFLAGS) $^ -o $@

bonus:		$(BOBJ)
	$(CC) $(CFLAGS) $(CPPFLAGS) $^ -o $(NAME)
	touch bonus

clean:
	rm -f $(OBJ) bonus

fclean:		clean
	rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re bonus
