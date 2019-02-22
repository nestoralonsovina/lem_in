/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalonso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 11:41:24 by nalonso           #+#    #+#             */
/*   Updated: 2019/02/22 18:23:25 by nalonso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "../libftprintf/includes/ft_printf.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

/*
** dynamic data structures and related functions
*/

typedef struct	s_dtab
{
	char	**array;
	size_t	used;
	size_t	size;
}				t_dtab;

void			init_dtab(t_dtab *a, size_t initial_size);
void			insert_dtab(t_dtab *a, char *element);
void			free_dtab(t_dtab *a);
void			index_dtab(t_dtab *a, char *element, size_t index);
void			**realloc_tab(void **ptr, size_t new_size, size_t original_size);

/*
** adjacency list representation of a graph
*/

typedef struct s_node t_node;
typedef struct s_graph t_graph;

struct	s_node
{
	int			vertex;
	t_node		*next;
};

struct	s_graph
{
    int 			num_vertices;
    t_node			**adj_list;
	int				*visited;
};


/*
** lem-in structures and functions
*/

typedef struct	s_lm
{
	t_dtab		rooms;
	int			ants;
	int			nb_rooms;
	t_graph		grap;
}				t_lm;

void	read_graph_improved(t_lm *lm);

/*
** debug option (-d) functions
*/

void		print_matrix(int **matrix, int rows, int cols);

#endif
