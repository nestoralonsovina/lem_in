#ifndef LEM_IN_H
# define LEM_IN_H

# include "../libftprintf/includes/ft_printf.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

# define PRINTABLE_SIZE 93

/*
** adjacency list representation of a graph
*/

typedef struct s_node	t_node;
typedef struct s_graph	t_graph;
typedef struct s_edge	t_edge;

typedef enum	s_bool
{
	false, true
}				t_bool;

struct	s_node
{
	char		*name;
	int			*links;
	size_t		nb_links;
	t_point		pos;
};

struct	s_graph
{
	int				adj_vert;
	int				adj_size;
    t_node			**adj_list;
	int				*visited;
	int 			**flow;
	int 			*pred;
};

/*
** Trie structure
*/

typedef struct s_trie	t_trie;

struct s_trie
{
	char	value;
	int		count;
	t_trie	*children[93];
};

t_trie	*trie_create(void);
void	insert_trie(t_trie *root, char *key);
int		search_trie(t_trie *root, char *key);

/*
 ** Queue structure
 */

typedef struct s_queue
{
	size_t		front;
	size_t		rear;
	size_t		size;
	size_t		capacity;
	int			*array;
}				t_queue;

t_queue	*create_queue(size_t capacity);
void	enqueue(t_queue *queue, int item);
int		dequeue(t_queue *queue);
int		front(t_queue *queue);
int		rear(t_queue *queue);

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

int		add_edge(t_graph *graph, int src, int dst);
void	init_graph(t_graph *g, size_t initial_size);
void	print_path(t_graph *g);
int		get_index(t_node **adj_list, char *name);
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

#endif
