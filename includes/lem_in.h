/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalonso <nalonso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 17:27:43 by jallen            #+#    #+#             */
/*   Updated: 2019/06/22 20:30:19 by nalonso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

# include "../libft/includes/libft.h"
# include "../libft/includes/avl.h"
# include "../libft/includes/queue.h"
# include "../libft/includes/gnl.h"

# define BACKWARD 1
# define FORWARD 2
# define D (1 << 0)
# define I (1 << 1)
# define P (1 << 2)
# define NM (1 << 3)
# define V (1 << 4)
# define ERROR_INVALID_ROOM "ERROR: invalid room"
# define ERROR_REPEATED_ROOM "ERROR: repeated room name"
# define ERROR_MALLOC "ERROR: malloc() failed"
# define ERROR_REPEATED_COORD "ERROR: two rooms have the same coordenates"

t_garbage			g_gb;

/*
** adjacency list representation of a graph
*/

typedef struct		s_edge
{
	int				to;
	int				from;
	int				flow;
	int				capacity;
	struct s_edge	*rev;
}					t_edge;

typedef struct		s_node
{
	char			*name;
	t_edge			**links;
	size_t			nb_links;
	t_edge			*incoming;
	int				flow;
	int				cost;
	int				ant;
	int				blocked;
	int				prev_index;
	int				type;
	int				in_node;
	int				out_node;
}					t_node;

typedef struct		s_room
{
	char			*name;
	int				index;
}					t_room;

typedef struct		s_counters
{
	int				cnt;
	int				move;
	int				sp;
}					t_counters;

typedef struct		s_graph
{
	t_room			source;
	t_room			sink;
	int				adj_vert;
	int				adj_size;
	int				nb_ant;
	int				nb_p;
	int				predicted;
	t_node			**adj_list;
	t_edge			**pred;
}					t_graph;

typedef struct		s_bfs
{
	t_queue			q;
	t_edge			**prev;
	int				*dist;
	int				*cost;
	int				*visited;
	char			last_edge;
}					t_bfs;

/*
** lem-in structures and functions
*/

typedef struct		s_path
{
	t_node			*room;
	int				len;
	int				ant;
}					t_path;

typedef struct		s_paths {
	t_edge			**path;
	t_path			**move;
	int				len;
	int				bg;
	int				ants;
	double			predicted_ants;
	struct s_paths	*next;
}					t_paths;

typedef struct		s_env
{
	t_garbage		gb;
	t_node			*end;
	t_avl			rooms;
	t_avl			coords;
	int				curr_nb_paths;
	int				best_iteration;
	t_paths			**paths;
	char			*line;
	int				nb_room;
	int				error;
	t_graph			graph;
	int				debug;
	int				bg;
}					t_env;

void				redo_graph(t_graph *g, t_graph *special);
/*
** path_management.c and compute_ants.c
*/

double				compute_ants(t_paths *head, t_paths *curr, t_graph *g);
t_paths				*trim_paths(t_paths *head, t_graph *g);
double				calculate_ants(t_paths *head, t_graph *g);

/*
** move_ants && init_paths.c
*/

int					plen(t_edge **p);
int					*create_index(t_path **path);
void				play(t_graph *g, t_paths *head, int debug);
void				init_path(t_paths *head, t_graph *g);
void				play_visu(t_graph *g, t_paths *head, int debug);
t_path				**create_path(t_graph *g, t_edge **path);
t_path				*new_path_node(t_node *r, int len, int ant);

/*
** graph.c
*/

void				start_links(t_graph *g);
int					add_edge(t_graph *graph, int src, int dst);
void				init_graph(t_graph *g, size_t initial_size);
int					get_index(t_node **adj_list, char *name);
void				append_node(t_graph *g, t_node *new_node);
void				free_graph(t_graph *g);
t_node				*create_node(char *name);

/*
** path utils
*/

void				print_path(t_path **path);
t_edge				**make_path(t_edge **prev, int l, int d);
t_edge				**push_edge(t_edge **path, t_edge *new_edge);

/*
** transfrom_paths.c
*/

t_edge				*spe_add_edge(t_graph *g, int src, int dst);
void				transform_paths(t_env env, t_graph *sp, t_paths **head_ref);
void				spe_start_links(t_graph *sp);

/*
** parse.c
*/

int					read_rooms(t_env *env);
void				read_links(t_env *env);
unsigned long		djb2(char *str);
int					read_ants(t_env *env);

/*
** bfs_utils.c
*/

void				bfs_run_iteration(t_bfs *bfs, t_graph *g);
void				bfs_reset_struct(t_bfs *bfs, int nodes, int src);
void				bfs_init(t_bfs *bfs, int nodes);
void				bfs_free(t_bfs *bfs);

/*
** debug.c
*/

void				d_print_links(t_graph *g);
void				d_print_path(t_edge **path, t_graph g);
void				d_print_paths(t_paths *head);
void				d_print_moves(t_path **move);
void				info_paths(t_paths *head, t_graph *g, int cnt, int debug);

/*
** utils.c
*/

int					print_error(void);
int					lem_in_gnl(char **line, int return_file);
void				append_path(t_paths **head, t_paths *new_path);
int					count_paths(t_paths *head);
t_paths				*new_path(t_edge **p, int bg);
void				print_file(int debug);

/*
** algo.c
*/

void				merge_sort(t_paths **head_ref);
int					save_paths(t_env *env, t_graph *sp);
void				algo(t_env env, t_graph *g);

#endif
