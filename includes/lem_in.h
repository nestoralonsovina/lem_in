#ifndef LEM_IN_H
#define LEM_IN_H

#include "../libftprintf/includes/ft_printf.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct	s_dtab 
{
	char	**array;
	size_t	used;
	size_t	size;
}				t_dtab;

typedef struct	s_lm
{
	t_dtab		rooms;
	size_t		ants;
	int			**graph;
}				t_lm;

void			init_dtab(t_dtab *a, size_t initial_size);
void			insert_dtab(t_dtab *a, char *element);
void			free_dtab(t_dtab *a);
void			print_dtab(t_dtab a);

#endif
