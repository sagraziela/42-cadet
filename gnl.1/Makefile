# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: root <root@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/19 11:35:37 by gde-souz          #+#    #+#              #
#    Updated: 2023/08/24 18:51:34 by root             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc -Wall -Wextra -Werror
AR = ar -rcs
NAME = get_next_line.a
SRC = get_next_line.c \
		get_next_line_utils.c
OBJ = $(SRC:%.c=%.o)
HD = ./get_next_line.h

all: $(NAME)

$(NAME): $(OBJ)
	$(AR) $(NAME) $(OBJ)

%.o: %.c
	$(CC) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
	rm -f $(HD)*.gch

re: fclean all

.PHONY: all clean fclean re