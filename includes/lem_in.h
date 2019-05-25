#ifndef LEM_IN_H
# define LEM_IN_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include "../libft/includes/libft.h"

# include "../libft/includes/avl.h"
# include "../libft/includes/queue.h"
# include "../libft/includes/gnl.h"

# define ERROR_INVALID_ROOM "ERROR: invalid room"
# define ERROR_REPEATED_ROOM "ERROR: repeated room name"
# define ERROR_MALLOC "ERROR: memory allocation with malloc() failed"
# define ERROR_REPEATED_COORD "ERROR: two rooms have the same coordenates"

/*
 ** adjacency list representation of a graph
 */

typedef struct s_node	t_node;
typedef struct s_graph	t_graph;
typedef struct s_edge	t_edge;
typedef struct	s_edge
{
    int			to;
    int			from;
    int         visited;
    struct s_edge *rev;
}				t_edge;

struct	s_node
{
    char		*name;
    t_edge		**links;
    size_t		nb_links;
    int 		cost;
    int			flow;
	int			ant;
};

typedef struct s_room
{
    char 	*name;
    int 	index;
}				t_room;

typedef struct	s_graph
{
    t_room		source;
    t_room		sink;
    int 		adj_vert;
    int 		adj_size;
    int			nb_ant;
    t_node		**adj_list;
    t_edge		**pred;
}				t_graph;

/*
 ** lem-in structures and functions
 */

typedef struct	s_env
{
    t_node		*end;
    t_avl		rooms;
    t_avl       coords;
    char		*line;
    int			nb_room;
    t_graph		graph;
    int			debug;
}				t_env;

/*
 ** Move ants
 */

typedef struct	s_path
{
    t_node	*room;
    int 	len;
    int 	ant;
}				t_path;

typedef struct	s_paths {
    t_edge			**path;
	t_path			**move;
	int				len;
	double			predicted_ants;
    struct s_paths	*next;
}				t_paths;


t_paths *trim_paths(t_paths *head, t_env env, t_graph *g);
double compute_ants(t_paths *head, t_paths *cur, t_graph *g);
t_path	**create_path(t_graph *g, t_edge **path);
void	print_path(t_path **path);
void	move_ant(t_path **path, int nb_ant, int last_path);
void	play(t_graph *g, t_paths *head);
int		plen(t_edge **p);

/*
**
** graph.c
**
*/

void	start_links(t_graph *g);
int		add_edge(t_graph *graph, int src, int dst);
void	init_graph(t_graph *g, size_t initial_size);
int		get_index(t_node **adj_list, char *name);
void	append_node(t_graph *g, t_node *new_node);
void	free_graph(t_graph *g);
t_node	*create_node(char *name);

/*
**
** path utils
**
*/

void	unvisit_path(t_edge **path, t_edge *intersection);
int		path_repeated(t_paths *head, t_edge **tmp);
int		path_goes_backwards(t_paths *head, t_edge **tmp, t_graph *g);
t_edge	**make_path(t_edge **prev, int l, int d);
t_edge	**push_edge(t_edge **path, t_edge *new_edge);


/*
**
** parse.c
**
*/

int				read_rooms(t_env *env);
int				read_links(t_env *env);
unsigned long	djb2(char *str);
int				read_ants(t_env *env);

/*
**
** debug.c
**
*/

void			d_print_links(t_graph *g);
void			d_print_path(t_edge **path, t_graph g);
void            d_print_paths(t_paths *head, t_graph *g);
/*
**
** utils.c
**
*/
int		print_error(void);
int			lem_in_gnl(char **line, int return_file);
t_edge *intersects(t_paths *known_paths, t_edge *p);
void	append_path(t_paths **head, t_paths *new_path);
int		count_paths(t_paths *head);
t_paths *new_path(t_edge **p);
t_paths *delete_superposition(t_paths *head, t_env env, t_graph *g);
void    delete_node(t_paths **head_ref, int key);
/*
**
** algo.c
**
*/
void		algo(t_env env, t_graph *g);
void		merge_sort(t_paths **head_ref);
#endif
