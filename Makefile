ccred="\033[0;31m"
ccyellow="\033[0;33m"
ccend="\033[0m"
ccgreen= "\033[0;32m"

# compiler

CC = gcc

# compilation flags

FLAGS = -Wall -Wextra

# program name

NAME = lem-in

# library including ft_printf and libft

LIBFT = libftprintf

# folders

DIR_S = src

DIR_O = temporary

DIR_H = includes

# source files for the project

SOURCES = dynamic_adj.c		\
		  dynamic_array.c	\
		  parse.c			\
		  trie.c			\
		  graph.c			\
		  bfs.c				\
		  queue.c			\
		  edmonds_karp.c	\
		  new_parse.c		\
		  move_ants.c		\
		  binary_heap.c		\
		  main.c

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
	@printf $(ccgreen)"compiled\t"$(ccend)
	@printf "$<\n"
	@mkdir -p temporary
	@$(CC) $(FLAGS) -I $(DIR_H) -o $@ -c $<


lib:
	@echo "Compiling libraries:"
	@printf $(ccyellow)"%-20s"$(ccred) $(LIBFT)
	@make -C $(LIBFT)

clean:
	@rm -f $(OBJS)
	@printf $(ccred)"temporary/*.o && temporary/\n"$(ccend)
	@rm -rf $(DIR_O)
	@printf $(ccred)"%s\n"$(ccend) $(LIBFT)
	@make clean -C $(LIBFT)

fclean: clean
	@rm -rf $(NAME) $(NAME).dSYM
	@printf $(ccred)"%s\n"$(ccend) $(NAME)
	@make fclean -C $(LIBFT)
	@printf $(ccred)"%s.a\n"$(ccend) $(LIBFT)

re: fclean all

.PHONY: clean fclean all re
