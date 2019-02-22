# compiler

CC = gcc

# compilation flags

FLAGS = -Wall -Wextra -Werror

# program name

NAME = lem-in

# library including ft_printf and libft

LIBFT = libftprintf

# folders

DIR_S = src

DIR_O = temporary

DIR_H = includes

# source files for the project

SOURCES = dynamic_array.c	\
		  lem-in.c

# header files

HEADER = lem_in.h

# prefixing

SRCS = $(addprefix $(DIR_S)/,$(SOURCES))

OBJS = $(addprefix $(DIR_O)/,$(SOURCES:.c=.o))

# compile project

all: $(NAME)

$(NAME): $(OBJS) lib
	@gcc -o $(NAME) $(FLAGS) -I $(DIR_H) $(OBJS) $(LIBFT)/libftprintf.a
	@echo "lem-in compiled"

$(DIR_O)/%.o: $(DIR_S)/%.c
	@echo "compiled\t$<"
	@mkdir -p temporary
	@$(CC) $(FLAGS) -I $(DIR_H) -o $@ -c $<

lib:
	@echo "Compiling libraries:"
	@echo "FT_PRINTF\t\c"
	@make -C $(LIBFT)

clean:
	@rm -f $(OBJS)
	@rm -rf $(DIR_O)
	@make clean -C $(LIBFT)

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIBFT)

re: fclean all


.PHONY: clean fclean all re
