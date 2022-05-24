# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: min-jo <min-jo@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/11 16:17:45 by min-jo            #+#    #+#              #
#    Updated: 2022/05/24 23:11:51 by min-jo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	pipex

HD_DIR		=	include/
SRC_DIR		=	src/

SRC_ORI		=	pipex.c perrors.c io_perrors.c string.c split.c quote.c\
				quote_counter_state.c
BSRC_ORI	=

SRC			=	$(addprefix $(SRC_DIR), $(SRC_ORI))
BSRC		=	$(addprefix $(SRC_DIR), $(BSRC_ORI))

OBJ			=	$(SRC:.c=.o)
BOBJ		=	$(BSRC:.c=.o)

CFLAGS		+=	-Wall -Wextra -Werror -MD
CPPFLAGS    +=	-I $(HD_DIR)
# LIBADD	+=	-lpthread
# LDFALGS	+=

all:		$(NAME)

%.o:		%.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $< -c -o $@

$(NAME):	$(OBJ)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(LIBADD) $^ -o $@

bonus:		$(BOBJ)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(LIBADD) $^ -o $(NAME)
	touch bonus

clean:
	rm -f $(OBJ)
	r m -f $(BOBJ)
	rm -f $(OBJ:.o=.d)
	rm -f $(BOBJ:.o=.d)
	rm -f bonus

fclean:		clean
	rm -f $(NAME)

re:
	make fclean
	make all

.PHONY:		all clean fclean re bonus

-include $(OBJ:.o=.d)
-include $(BOBJ:.o=.d)
