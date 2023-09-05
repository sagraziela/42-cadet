# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/19 11:35:37 by gde-souz          #+#    #+#              #
#    Updated: 2023/09/05 13:50:59 by gde-souz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc -Wall -Wextra -Werror
AR = ar -rcs
NAME = libft.a
BUILD = ./build_libft/
SRC = ft_isalpha.c \
		ft_isdigit.c \
		ft_isalnum.c \
		ft_isascii.c \
		ft_isprint.c \
		ft_strlen.c \
		ft_memset.c \
		ft_bzero.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_strlcpy.c \
		ft_strlcat.c \
		ft_toupper.c \
		ft_tolower.c \
		ft_strchr.c \
		ft_strrchr.c \
		ft_strncmp.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_strnstr.c \
		ft_atoi.c \
		ft_calloc.c \
		ft_strdup.c \
		ft_substr.c \
		ft_strjoin.c \
		ft_strtrim.c \
		ft_split.c \
		ft_itoa.c \
		ft_strmapi.c \
		ft_striteri.c \
		ft_putchar_fd.c \
		ft_putstr_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c

BONUS_SRC = ft_lstnew.c \
			ft_lstadd_front.c \
			ft_lstsize.c \
			ft_lstlast.c \
			ft_lstadd_back.c \
			ft_lstdelone.c \
			ft_lstclear.c \
			ft_lstiter.c \
			ft_lstmap.c

OBJ = $(addprefix $(BUILD), $(SRC:%.c=%.o))
BONUS_OBJ = $(addprefix $(BUILD), $(BONUS_SRC:%.c=%.o))
HD = ./libft.h

all: $(NAME)

$(BUILD)%.o:%.c
	@mkdir -p $(BUILD)
	@$(CC) -c $< -o $@ -I $(HD)

$(NAME): $(OBJ)
	@$(AR) $(NAME) $(OBJ)

bonus: $(BONUS_OBJ)
	@$(AR) $(NAME) $(BONUS_OBJ)

clean:
	@rm -f $(OBJ) $(BONUS_OBJ)

fclean: clean
	@rm -f $(NAME)
	@rm -f $(HD)*.gch

re: fclean all

.PHONY: all clean fclean re bonus