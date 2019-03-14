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
	int 		cost;
};

typedef struct s_avl_node
{
	int 				index;
	int 				height;
	char 				*key;
	struct	s_avl_node	*left;
	struct	s_avl_node	*right;
}				t_avl_node;

struct	s_graph
{
	int				adj_vert;
	int				adj_size;
    t_node			**adj_list;
	int				*visited;
	int 			**flow;
	int 			*pred;
	int 			*dist;
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
 * Priority queue implemented with binary heap
 */

typedef struct	s_element
{
	int			id;
	int			priority;
}				t_element;

typedef struct	s_binary_heap
{
	int			n;
	t_element	*elements;
	int			*pos;
	int			(*smallest)(struct s_binary_heap *self);
	void		(*insert)(struct s_binary_heap *self, int id, int priority);
	void		(*decrease_key)(struct s_binary_heap *self, int id, int np);
	int			(*is_empty)(struct s_binary_heap *self);
}				t_binary_heap;

int				bh_smallest(struct s_binary_heap *bh);
void			bh_insert(struct s_binary_heap *bh, int id, int priority);
void			bh_decrease_key(struct s_binary_heap *bh, int id, int new_priority);
int				bh_is_empty(struct s_binary_heap *bh);
t_binary_heap	bh_init(int capacity);

/*
** lem-in structures and functions
*/

typedef struct	s_env
{
	int 		i_end;
	int 		i_start;
	t_node		*end;
	char		*line;
	int			nb_ant;
	int			nb_room;
	t_graph		graph;
	t_avl_node	*head;
}				t_env;

/*
** Move ants
*/

typedef struct	s_path
{
	t_node	*room;
	int		cost;
	int 	len;
	int 	ant;
}				t_path;

t_path	**create_path(t_graph *g);
void	print_path(t_path **path);
void	move_ant(t_path **path, t_env *env);
void	make_movements(t_graph *g, t_env *env);

/*
** set of functions to create and manage a graph in the form of an 
** adjacency list
*/

int		add_edge(t_graph *graph, int src, int dst);
void	init_graph(t_graph *g, size_t initial_size);
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
