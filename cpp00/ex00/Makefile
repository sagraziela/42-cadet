NAME = megaphone
CPPFLAGS = c++ -Wall -Wextra -Werror -g -std=c++98
SRC = ./megaphone.cpp

# Objects
OBJ = $(notdir $(SRC:.cpp=.o))

# Default target to compile the mandatory part
all: $(NAME)

# Color codes of output on terminal
GREEN = \e[1;32m
WHITE = \033[1;37m
CYAN= \033[0;36m
END = \033[0m

# Target to build the mandatory part
$(NAME): $(OBJ)
	@ $(CPPFLAGS) $(OBJ) -o $@
	@echo "$(GREEN)--------------------------------------------------$(END)"
	@echo "$(GREEN)The [$(CYAN)CPP-00 MEGAPHONE$(GREEN)] has been compiled!$(END)"
	@echo "$(GREEN)--------------------------------------------------$(END)"

valgrind: all
	@echo "Running the program with valgrind..."
	valgrind --leak-check=full --show-leak-kinds=all --trace-children=yes --track-origins=yes ./megaphone 

run: all
	@echo "Running the program..."
	./megaphone

# Builds mandatory object files
%.o: %.cpp
	$(CC) -c $(CFLAGS) $< -o $@

# Cleans object files and dependencies
clean:
	@rm -f %.o
	@echo "$(WHITE)---------------------------------------$(END)"
	@echo "$(WHITE)    Object files were cleaned! 🧹✨$(END)"
	@echo "$(WHITE)---------------------------------------$(END)"

# Cleans the executable file and pre-compiled header
fclean: clean
	@rm -f $(NAME)
	@echo "$(WHITE)---------------------------------------$(END)"
	@echo "$(WHITE)   Executable file was cleaned! 🧹✨$(END)"
	@echo "$(WHITE)---------------------------------------$(END)"

# Cleans everything generated by the Makefile and rebuild it all
re: fclean all

# Phony targets
.PHONY: all clean fclean re run valgrind
