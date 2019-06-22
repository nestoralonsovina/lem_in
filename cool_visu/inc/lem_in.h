/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbally <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 17:43:55 by hbally            #+#    #+#             */
/*   Updated: 2019/03/19 17:43:57 by hbally           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include <stdint.h>
# include <stdlib.h>

/*
** Macros for error reporting
*/

# define OK 0
# define KO 1
# define DONE 2

/*
** Macros for node types
*/

# define START 1
# define END 2

/*
** Macros for turn control
*/

# define TURN_START -1
# define TURN_END -2
# define LAST_TURN_END -3

/*
** Generic list structure
*/

typedef struct		s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

/*
** Options
*/

typedef struct		s_opt_index
{
	uint16_t		export:		1;
	uint16_t		verbose:	1;
}					t_opt_index;

typedef union		u_opt
{
	t_opt_index		dict;
	uint16_t		opt_int;
}					t_opt;

/*
** Hash Table
*/

typedef struct		s_table
{
	t_list			**tab;
	int				size;
}					t_table;

/*
** Sub-Components for node structure
**	- gate_data : information about gate nodes
**	- hop : next node in path for a given flow id
**  - vector : node coordinates
*/

typedef struct		s_gate_data
{
	int				flow;
	int				path_len;
	int				crowding;
	int				sent;
}					t_gate_data;

typedef struct		s_hop
{
	int				flow;
	struct s_node	*hop_to;
}					t_hop;

typedef struct		s_vector
{
	int				x;
	int				y;
}					t_vector;

/*
** Main Node Component
*/

typedef struct		s_node
{
	uint8_t			type;
	char			*name;
	int				guest;
	t_vector		coord;
	t_list			*edges;
	t_list			*hop_data;
	t_list			*gate_data;
	int				last_visited;
	int				residual;
	struct s_node	*parent;
	int8_t			value;
}					t_node;

/*
** Graph representation of input map
*/

typedef struct		s_graph
{
	t_list			**nodes;
	int				table_size;
	t_node			*source;
	t_node			*sink;
	int				source_capacity;
	int				flow_max;
	int				flow_best;
	int				flow_best_cost;
}					t_graph;

/*
** Breadth-First Search / Simulation data containers
*/

typedef struct		s_bfs
{
	t_list			*level;
	t_list			*frontier;
	t_list			*frontier_end;
}					t_bfs;

/*
** Container for program data
*/

typedef struct		s_wrap
{
	t_graph			graph;
	t_opt			opt;
	t_list			*input_start;
	t_list			*input_end;
	t_bfs			*bfs_state;
	t_list			*bfs_output;
	int				out_fd;
}					t_wrap;

/*
** Options
*/

void				get_options(t_opt *opt, int argc, char **argv);

/*
**	Parsing
*/

int					ft_read_map(t_wrap *wraper, t_graph *graph);
void				ft_make_tab(int size, t_wrap *wraper, t_graph *graph);
void				ft_get_coord(char *str, t_node **node, t_wrap *wraper);
void				ft_init_graph(t_wrap *wraper,
									t_table *table,
									t_graph *graph);
void				ft_make_node(t_wrap *wraper, char *str,
									t_graph *graph, int *type);
int					ft_make_graph(t_wrap *wraper, int size, t_graph *graph);
int					ft_nbr_size(int nbr);
int					ft_ants(char *line, t_wrap *wraper, int ants);
unsigned long		hash(unsigned char *str);
int					ft_is_node(char *line, t_wrap *wraper);
int					ft_is_link(char *line, t_wrap *wraper, t_list **prec);
int					ft_is_comment(t_wrap *wraper, char *str, int past);
void				ft_get_edges(char **room_1, char **room_2,
									char *str, t_wrap *wraper);
int					ft_add_edges(char **room_1, char **room_2, t_wrap *wraper,
t_graph *graph);
void				ft_insert_in_tab(t_wrap *wraper, t_graph *graph,
									int index, t_node *new_node);
void				ft_print_hash_tab(t_graph *graph, int full);
t_node				*ft_get_hashed(char *str, t_graph *graph);
void				ft_free_wrap(t_wrap *wrap);
void				ft_free_hop(t_node *node);
void				ft_mid_file(t_wrap *wraper, int flag, t_list **lst);
void				ft_free_list(t_list *lst);
void				output_wrapper(t_wrap *wrap, t_graph *graph);

/*
**	List Creation/Deletion
*/

void				add_start(t_wrap *wrap, void *content, t_list **start);
void				add_end(t_wrap *wrap, void *content,
								t_list **start, t_list **end);
void				del_one(t_list *elem, t_list **start);
void				del_all(t_list **start);

/*
**	Create all possible flows and store them
*/

void				flow_create_all(t_wrap *wrap, t_graph *graph);
void				flow_find_wrapper(t_wrap *wrap, t_graph *graph);
void				flow_find_new(t_wrap *wrap, int flow, t_node *source);
void				flow_update_nodes(t_wrap *wrap, t_list *path, int flow);
void				flow_update_gates(t_wrap *wrap, t_node *source, int flow);

/*
** 	Cost calculation for a given flow
*/

t_gate_data			*get_data(t_list *data_list, int flow);
t_node				*get_best_gate(t_node *source, int flow);
void				flow_simulate(t_graph *graph, t_node *source, int flow);

/*
** Output
*/

void				output_result(t_wrap *wrap, t_node *source,
									int flow, int remain);
void				output_mapdata(t_list *input);

/*
** Helpers
*/

uint8_t				update_level(t_list **level, t_list **frontier);
t_node				*hop_get(t_list	*hop_list);
t_node				*hop_get_flow(t_list *hop_list, int flow);

/*
**	Collector for clean exit
*/

void				collector(t_wrap *wrap, uint8_t flag);

/*
** Viz functions
*/

void				graph_to_file(t_wrap *wrap, t_graph *graph);
void				parse_table(t_wrap *wrap, t_graph *graph, t_list **nodes,
									void (*action)(t_wrap*, t_list*));
void				move_to_file(t_wrap *wrap, t_node *source, t_node *target,
									int	flag);
void				edges_to_file(t_wrap *wrap, t_list *start);
void				nodes_to_file(t_wrap *wrap, t_list *start);
int					create_file(t_wrap *wrap, char *path);

#endif
