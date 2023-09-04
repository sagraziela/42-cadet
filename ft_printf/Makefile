# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gde-souz <gde-souz@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/04 16:42:26 by gde-souz          #+#    #+#              #
#    Updated: 2023/09/04 17:54:55 by gde-souz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
CC = cc -Wall -Wextra -Werror
AR = ar -rcs

PATH_LIBFT = ./libft/
LIBFT = $(addprefix $(PATH_LIBFT), libft.a)

MANDATORY_BUILD = ./build_mandatory/
MANDATORY_SRC = ./ft_printf.c
MANDATORY_OBJ = $(addprefix $(MANDATORY_BUILD), $(MANDATORY_SRC:%.c=%.o))

HD = ./ft_printf.h

all: $(NAME)

# Buildind object files
$(MANDATORY_BUILD)%.o:%.c
	mkdir -p $(MANDATORY_BUILD)
	$(CC) -I $(HD) -c $< -o $@

$(LIBFT):
	make -C $(PATH_LIBFT)

$(NAME): $(LIBFT) $(MANDATORY_OBJ)
	cp $(LIBFT) $(NAME)
	$(AR) $(NAME) $(MANDATORY_OBJ)

clean: clean_libft
	rm -rf $(MANDATORY_OBJ)

fclean: clean fclean_libft
	rm -f $(NAME)
	rm -f $(HD)*.gch

clean_libft:
	make clean -C $(PATH_LIBFT)

fclean_libft:
	make fclean -C $(PATH_LIBFT)

re: fclean all

.PHONY: all clean fclean clean_libft fclean_libft re