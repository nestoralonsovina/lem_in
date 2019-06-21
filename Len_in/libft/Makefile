# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hbally <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            # #    Created: 2018/11/06 14:02:29 by hbally            #+#    #+#              #
#    Updated: 2019/01/21 13:13:56 by hbally           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				=	libft.a

# Dir Variables

SRCSDIR   			=	srcs

OBJSDIR   			=	objs

MAIN_LIBDIR			=	libs

LIBDIRS				:=	$(MAIN_LIBDIR)/libftprintf

INCLUDES			=	-I includes

# File Variables

SRCS_RAW			:=	ft_atoi.c 				\
						ft_bzero.c 				\
						ft_isalnum.c 			\
						ft_isalpha.c 			\
						ft_isascii.c 			\
						ft_isdigit.c			\
						ft_isprint.c			\
						ft_itoa.c				\
						ft_memalloc.c		 	\
						ft_memccpy.c	 		\
						ft_memchr.c 			\
						ft_memcmp.c 			\
						ft_memcpy.c 			\
						ft_memdel.c 			\
						ft_memmove.c	 		\
						ft_memset.c 			\
						ft_putchar.c	 		\
						ft_putchar_fd.c 		\
						ft_putendl.c	 		\
						ft_putendl_fd.c 		\
						ft_putnbr.c 			\
						ft_putnbr_fd.c	 		\
						ft_putstr.c 			\
						ft_putstr_fd.c	 		\
						ft_strcat.c				\
						ft_strchr.c 			\
						ft_strchri.c 			\
						ft_strclr.c 			\
						ft_strcmp.c 			\
						ft_strcpy.c 			\
						ft_strdel.c 			\
						ft_strdup.c 			\
						ft_strequ.c 			\
						ft_striter.c	 		\
						ft_striteri.c	 		\
						ft_strjoin.c	 		\
						ft_strlcat.c	 		\
						ft_strlen.c 			\
						ft_strmap.c 			\
						ft_strmapi.c	 		\
						ft_strncat.c	 		\
						ft_strncmp.c	 		\
						ft_strncpy.c	 		\
						ft_strnequ.c	 		\
						ft_strnew.c 			\
						ft_strnstr.c	 		\
						ft_strrchr.c	 		\
						ft_strsplit.c			\
						ft_strstr.c 			\
						ft_strsub.c 			\
						ft_strtrim.c	 		\
						ft_tolower.c	 		\
						ft_toupper.c	 		\
						ft_str_realloc.c		\
						ft_memrealloc.c			\
						ft_sqrt.c				\
						ft_int_swap.c			\
						ft_atol.c				\
						ft_atoll.c				\
						ft_ltoa.c				\
						ft_uitoa.c				\
						ft_ultoa.c				\
						ft_ulltoa.c				\
						ft_uitoxa.c				\
						ft_ultoxa.c				\
						ft_ulltoxa.c			\
						ft_uitooa.c				\
						ft_ultooa.c				\
						ft_ulltooa.c			\
						ft_dtoa.c				\
						ft_ldtoa.c				\
						ft_abs16.c				\
						ft_abs32.c				\
						ft_abs64.c				\
						ft_abstime.c			\
						ft_round_double.c		\
						ft_iswhitespace.c		\
						ft_strclen.c			\
						ft_strcdup.c			\
						get_next_line.c

# 						END OF SRCS_RAW

SRCS				:=	$(SRCS_RAW:%.c=$(SRCSDIR)/%.c)

OBJS  				:=	$(SRCS:$(SRCSDIR)/%.c=$(OBJSDIR)/%.o)

LIBOBJS				:=	$(patsubst %, %/objs/*.o, $(LIBDIRS))

LIBFILES			:=	$(foreach LIB, $(LIBDIRS), $(LIB)/$(notdir $(LIB)).a)

DEPENDENCIES		:=	$(OBJS:%.o=%.d)

# Compiler Config

CC					=	gcc

CFLAGS				+=	-Wall -Werror -Wextra

# Main Target

all					:	makelibs $(NAME)


$(NAME)				: 	$(OBJS) $(LIBFILES)
						ar rc $@ $(OBJS)
						ar rc $@ $(LIBOBJS)
						ranlib $@

# Make Subsystems

.PHONY				:	makelibs
makelibs			:
						@$(foreach LIBDIR, $(LIBDIRS), make -C $(LIBDIR);)

# Compile Objs

-include $(DEPENDENCIES)

$(OBJS)				: 	$(OBJSDIR)/%.o : $(SRCSDIR)/%.c
						@mkdir -p objs
						$(CC) -o $@ $(CFLAGS) $(INCLUDES) -MMD -c $<

# Cleanup

.PHONY				:	clean
clean				:
						rm -f $(OBJS) $(DEPENDENCIES)
						rm -rf $(OBJSDIR)
						@$(foreach LIBDIR, $(LIBDIRS), make clean -C $(LIBDIR);)

.PHONY				:	fclean
fclean				:	clean
						rm -f $(NAME)
						@$(foreach LIBDIR, $(LIBDIRS), make fclean -C $(LIBDIR);)

.PHONY				:	re
re					:	fclean all
