# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/19 11:35:37 by gde-souz          #+#    #+#              #
#    Updated: 2023/08/15 15:25:14 by gde-souz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc -Wall -Wextra -Werror
AR = ar -rcs
NAME = libft.a
SRC = ./src/ft_isalpha.c \
		./src/ft_isdigit.c \
		./src/ft_isalnum.c \
		./src/ft_isascii.c \
		./src/ft_isprint.c \
		./src/ft_strlen.c \
		./src/ft_memset.c \
		./src/ft_bzero.c \
		./src/ft_memcpy.c \
		./src/ft_memmove.c \
		./src/ft_strlcpy.c \
		./src/ft_strlcat.c \
		./src/ft_toupper.c \
		./src/ft_tolower.c \
		./src/ft_strchr.c \
		./src/ft_strrchr.c \
		./src/ft_strncmp.c \
		./src/ft_memchr.c \
		./src/ft_memcmp.c \
		./src/ft_strnstr.c \
		./src/ft_atoi.c \
		./src/ft_calloc.c \
		./src/ft_strdup.c \
		./src/ft_substr.c \
		./src/ft_strjoin.c \
		./src/ft_strtrim.c \
		./src/ft_split.c \
		./src/ft_itoa.c \
		./src/ft_strmapi.c \
		./src/ft_striteri.c \
		./src/ft_putchar_fd.c \
		./src/ft_putstr_fd.c \
		./src/ft_putendl_fd.c \
		./src/ft_putnbr_fd.c

BONUS_SRC = ./src/ft_lstnew.c \
			./src/ft_lstadd_front.c \
			./src/ft_lstsize.c \
			./src/ft_lstlast.c \
			./src/ft_lstadd_back.c \
			./src/ft_lstdelone.c \
			./src/ft_lstclear.c \
			./src/ft_lstiter.c \
			./src/ft_lstmap.c
OBJ = $(SRC:%.c=%.o)
BONUS_OBJ = $(BONUS_SRC:%.c=%.o)
HD = ./libft.h

all: $(NAME)

$(NAME): $(OBJ)
	$(AR) $(NAME) $(OBJ)

bonus: $(BONUS_OBJ)
	$(AR) $(NAME) $(BONUS_OBJ)

%.o: %.c
	$(CC) -c $< -o $@

clean:
	rm -f $(OBJ) $(BONUS_OBJ)

fclean: clean
	rm -f $(NAME)
	rm -f $(HD)*.gch

re: fclean all

.PHONY: all clean fclean re bonus