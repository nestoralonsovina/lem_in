#ifndef LEM_IN_H
# define LEM_IN_H

# include "../libftprintf/includes/ft_printf.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

/*
** adjacency list representation of a graph
*/

typedef struct s_node	t_node;
typedef struct s_graph	t_graph;
typedef struct s_edge	t_edge;

struct	s_node
{
	char		*name;
	int			*adj;
	int			nb_links;
	t_point		pos;
};

struct	s_graph
{
	int				adj_vert;
	int				adj_size;
    t_node			**adj_list;
	int				*visited;
};

/*
** lem-in structures and functions
*/

typedef struct	s_env
{
	char		*start;
	t_node		*end;
	char		*line;
	int			nb_ant;
	int			nb_room;
	t_graph		graph;
}				t_env;


/*
** set of functions to create and manage a graph in the form of an 
** adjacency list
*/

void	init_graph(t_graph *g, size_t initial_size);
void	append_node(t_graph *g, t_node *new_node);
void	free_graph(t_graph *g);
t_node	*create_node(char *name, int x, int y);

/*
** parse the input
*/

int		read_rooms(t_env *env);
int		read_links(t_env *env);
int		read_ants(t_env *env);

/*
** debug option (-d) functions
*/

void		print_matrix(int **matrix, int rows, int cols);

#endif
