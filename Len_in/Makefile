# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hbally <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/19 19:12:50 by hbally            #+#    #+#              #
#    Updated: 2019/03/20 10:25:39 by hbally           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				=	lem-in

# Dir Variables

SRCSDIR   			=	src

OBJSDIR   			=	obj

EXPORTDIR			=	viz/data

LIBSPATH			=	.

LIBDIRS				:=	$(LIBSPATH)/libft

INCDIR				:=	$(LIBDIRS:%=%/inc) 			\
						inc

# File Variables

SRCS_RAW			:=	main.c						\
						list_add.c					\
						list_del.c					\
						collector.c					\
						flow_create_all.c			\
						flow_find_new.c				\
						flow_update.c				\
						flow_simulate.c				\
						flow_helpers.c				\
						viz_tofile.c				\
						viz_tofile_helpers.c		\
						ft_read_map.c       		\
						ft_make_graph.c     		\
						ft_basic_read.c     		\
						ft_get_edges.c				\
						output_result.c				\
						output_mapdata.c			\
						input_getoptions.c			\
						ft_free_all.c

SRCS				:=	$(SRCS_RAW:%.c=$(SRCSDIR)/%.c)

OBJS  				:=	$(SRCS:$(SRCSDIR)/%.c=$(OBJSDIR)/%.o)

DEPENDENCIES		:=	$(OBJS:%.o=%.d)

LIBFILES			:=	$(foreach LIB, $(LIBDIRS), $(LIB)/$(notdir $(LIB)).a)

# Compiler Config

CC					=	gcc

CFLAGS				+=	-Wall -Werror -Wextra

INCLUDES			:=	$(addprefix -I ,$(INCDIR))

INCLIBS				:=	$(foreach LIB,$(LIBDIRS),-L $(LIB) $(subst lib,-l,$(notdir $(LIB))))

# Main Target

all					:	libs $(NAME)

$(NAME)				: 	$(OBJS) $(LIBFILES)
						@mkdir -p $(EXPORTDIR)
						$(CC) -o $@ $(CFLAGS) $(INCLIBS) $(OBJS)

# Make Libs

.PHONY				:	libs
libs				:
						@$(foreach LIB, $(LIBDIRS), make -C $(LIB);)

# Objs Target

-include $(DEPENDENCIES)

$(OBJS)				: 	$(OBJSDIR)/%.o : $(SRCSDIR)/%.c
						@mkdir -p $(OBJSDIR)
						$(CC) -o $@ $(CFLAGS) $(INCLUDES) -MMD -c $<

# Cleanup

.PHONY				:	clean
clean				:
						@$(foreach LIB, $(LIBDIRS), $(MAKE) -C $(LIB) clean ;)
						rm -f $(OBJS) $(DEPENDENCIES)
						rm -rf $(EXPORTDIR) $(OBJSDIR)

.PHONY				:	fclean
fclean				:	clean
						@$(foreach LIB, $(LIBDIRS), $(MAKE) -C $(LIB) fclean ;)
						rm -f $(NAME)

.PHONY				:	re
re					:	fclean all
