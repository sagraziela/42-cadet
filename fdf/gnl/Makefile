NAME = gnl.a
CFLAGS = -Wall -Wextra -Werror
INCLUDE = ../includes

SRC = get_next_line.c \
		get_next_line_utils.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@ -I $(dir $@)

$(NAME): $(OBJ)
	@ar -rcs $(NAME) $(OBJ)

clean:
	@$(RM) -rf *.o

fclean:
	@$(RM) -rf *.o
	@$(RM) -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
