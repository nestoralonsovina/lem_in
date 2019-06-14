/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalonso <nalonso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 17:46:54 by nalonso           #+#    #+#             */
/*   Updated: 2019/06/11 20:00:11 by nalonso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	d_print_node(t_node *n);

/*
**	EVERYTHING RELATED TO THE BFS STRUCTURE IS NOW HERE FOR EASIER MODIFICATIONS
*/

typedef struct		s_bfs
{
	t_queue			q;
	t_edge			**prev;
	int				*dist;
	int				*cost;
	int				*visited;
	char			last_edge;
}					t_bfs;

void	bfs_free(t_bfs *bfs)
{
	free(bfs->visited);
	free(bfs->dist);
	free(bfs->prev);
}

void	bfs_init(t_bfs *bfs, int nodes)
{
	bfs->prev = malloc(sizeof(t_edge *) * (nodes + 1));
	bfs->visited = malloc(sizeof(int) * (nodes + 1));
	bfs->dist = malloc(sizeof(int) * (nodes + 1));
	bfs->cost = malloc(sizeof(int) * (nodes + 1));
	bfs->last_edge = 0;
	if (!bfs->prev || !bfs->visited || !bfs->dist)
	{
		ft_putendl_fd(ERROR_MALLOC, 2);
		exit(EXIT_FAILURE);
	}
}

void	bfs_reset_struct(t_bfs *bfs, int nodes, int src)
{
	int	i;

	bfs->q = create_queue(nodes); // we are not using the queue each time
	if (!bfs->q.array)
	{
		ft_putendl_fd(ERROR_MALLOC, 2);
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < nodes)
	{
		bfs->prev[i] = NULL;
		bfs->dist[i] = 2147483647;
		bfs->cost[i] = 2147483647;
		i += 1;
	}
	bfs->dist[src] = 0;
	bfs->cost[src] = 0;
	bfs->q.push(&(bfs->q), src);
}

void	bfs_run_iteration(t_bfs *bfs, t_graph *g)
{
	t_edge	*tmp;
	int		cur;
	int		i;

	while (bfs->q.size != 0)
	{
		cur = bfs->q.pop(&(bfs->q));
		i = 0;
		while (i < (int)g->adj_list[cur]->nb_links)
		{
			tmp = g->adj_list[cur]->links[i];
			if (bfs->prev[tmp->to] == NULL \
				&& tmp->to != g->source.index
				&& tmp->flow == 1)
			{
				bfs->dist[tmp->to] = bfs->dist[tmp->from] + 1;
				bfs->prev[tmp->to] = tmp;
				bfs->q.push(&(bfs->q), tmp->to);
			}
			i += 1;
		}
	}
	free(bfs->q.array);
}

/*
**	END OF BFS UTILS THINGS
*/

/*
**	Full information: https://en.wikipedia.org/wiki/Bellman-Ford_algorithm
**	Bellman-Ford is an algorithm that computes the shortest paths from a single
**	source vertex to all of the other vertices in a weighted digraph.
*/

static int		check_back(t_graph *g, t_bfs *bfs, t_edge *e, int *weight)
{
	for (int i = 0; i < g->adj_list[e->to]->nb_links; i++)
	{
		if (g->adj_list[e->to]->links[i]->flow < 0 && g->adj_list[e->to]->links[i]->rev != e) 
		{
			*weight = 1;
			return (1);
		}
	}
	return (0);
}


static void		push_negatives(t_graph *g, t_bfs *bfs, int node)
{
	for (int i = 0; i < g->adj_list[node]->nb_links; i++)
	{
		if (g->adj_list[node]->links[i]->flow < 0) 
		{
			bfs->q.push(&bfs->q, g->adj_list[node]->links[i]->to);
		}
	}
}

void	bellman_ford(t_env env, t_graph *g, t_bfs *bfs)
{

	// This implementation takes in a graph, represented as lists of vertices and edges,
	// and fills two arrays (distance and predecessor) about the shortest patH From the source to each vertex
	ft_putendl(0);
	bfs_init(bfs, g->adj_vert);
	bfs_reset_struct(bfs, g->adj_vert, g->source.index);	// Initialize all the arrays to default values

	t_edge *e;
	while (bfs->q.size != 0)
	{
		int cur = bfs->q.pop(&(bfs->q));
		if (g->adj_list[cur]->incoming)
		{
			e = g->adj_list[cur]->incoming;
			int cost = -1;
			if (bfs->cost[e->to] + cost < bfs->cost[e->from])
			{
					bfs->cost[e->from] = bfs->cost[e->to] + cost;
					bfs->dist[e->from] = bfs->dist[e->to] + 1;
					bfs->prev[e->from] = e;
					bfs->q.push(&bfs->q, e->from);
					ft_printf("@ ");
					d_print_node(g->adj_list[e->from]);
					ft_putendl(0);
			}
		}
		for (size_t j = 0; j < g->adj_list[cur]->nb_links; j++)
		{
			e = g->adj_list[cur]->links[j];
			int cost = 1;
			if (e->capacity - e->flow > 0)
			{
				if (bfs->cost[e->from] + cost < bfs->cost[e->to])
				{
					bfs->cost[e->to] = bfs->cost[e->from] + cost;
					bfs->dist[e->to] = bfs->dist[e->from] + 1;
					bfs->prev[e->to] = e;
					bfs->q.push(&bfs->q, e->to);
					ft_printf("@ ");
					d_print_node(g->adj_list[e->to]);
					ft_putendl(0);
				}
			}
		}
		if (bfs->prev[g->sink.index] != NULL)
			break ;
	}
	free(bfs->q.array);
}

/*
**	Full information: https://en.wikipedia.org/wiki/Ford-Fulkerson_algorithm
**	Ford-fulkerson is a greedy algorithm that computes the maximum flow in a
**	flow network. The method to find the augmenting path is not defined, we're
**	using bellman-ford to do that.
*/

void	ford_fulkerson(t_env e, t_graph *g, t_bfs *bfs)
{
	t_paths *head = NULL;

	//ft_printf("Ford fulkerson...\n");
	//t_edge **tmp_path = make_path(bfs->prev, bfs->dist[g->sink.index], g->sink.index);
	//append_path(&head, new_path(tmp_path, 0));

	for (t_edge *e = bfs->prev[g->sink.index]; e != NULL;) 
	{
		d_print_node(g->adj_list[e->from]);
		ft_printf(" - ");
		d_print_node(g->adj_list[e->to]);
		ft_putendl(0);
		if (bfs->prev[e->from] != e)
		{
			g->adj_list[e->to]->incoming = e;
			e->flow += 1;
			e = bfs->prev[e->from];
		}
		else
		{
			g->adj_list[e->to]->incoming = NULL;
			e->flow -= 1;
			e = bfs->prev[e->to];
		}
		
	}
}

/*
**	Algo first part:
**	The idea here is that we'll some iterations, adjusting the flow through
**	the network until we reach the point of max flow and minimum cost.
*/

/*
**	The new idea:
**	I'll do one iteration of bellmand-ford
*/

void	part_one(t_env env, t_graph *g)
{
	int		mf;
	t_bfs	bfs;

	mf = 0;
	bfs_init(&bfs, g->adj_vert);
	while (1)
	{
		bellman_ford(env, g, &bfs);
		if (bfs.prev[g->sink.index] == NULL)
		{
			break ;
		}
		else
		{
			ford_fulkerson(env, g, &bfs);
			mf += 1;
		}
	}
	bfs_free(&bfs);
}

/*
**	Algo second part:
**	We'll now run a BFS through the network to find the correct paths, but we'll
**	put some constrains on it:
**		1. It won't go trough anything that wasn't modified by ford-fulkerson
**		2. The paths won't pass trough the points we're the flow is null (0).
**	That second point should be the only constrain that we need if everything is
**	working properly.
*/

void	part_two(t_env e, t_graph *g, t_paths **head_ref)
{
	t_bfs	bfs;
	t_paths	*head;

	bfs_init(&bfs, g->adj_vert);
	head = NULL;
	while (1)
	{
		bfs_reset_struct(&bfs, g->adj_vert, g->source.index);
		bfs_run_iteration(&bfs,  g);
		if (bfs.prev[g->sink.index] == NULL)
		{
			if (head == NULL)
				ft_fprintf(2, "Error: path not found\n");
			break;
		}
		t_edge **tmp_path;

		tmp_path = make_path(bfs.prev, bfs.dist[g->sink.index], g->sink.index);
		int i = 0;
		while (i < plen(tmp_path))
		{
			tmp_path[i]->flow = 0;
			i += 1;
		}
		append_path(&head, new_path(tmp_path, 0));
	}
	bfs_free(&bfs);
	*head_ref = head;
}

void	d_print_node(t_node *n)
{
	ft_printf("%s", n->name);
	if (n->type & 1)
	{
		ft_printf("_IN");
	}
	else if (n->type & 2)
	{
		ft_printf("_OUT");
	}
}

void	d_print_edges(t_env env, t_graph *g)
{
	int i;
	int j;

	i = 0;
	while (i < g->adj_vert)
	{
		j = 0;
		d_print_node(g->adj_list[i]);
		ft_printf(":\n");
		while (j < g->adj_list[i]->nb_links)
		{
			ft_printf("\t --> ");
			if (g->adj_list[i]->links[j])
			{
				d_print_node(g->adj_list[g->adj_list[i]->links[j]->to]);
				ft_printf(" @ %d", g->adj_list[i]->links[j]->flow);
			}
			else
			{
				ft_printf("(null)");
			}
			
			ft_putendl(0);
		j += 1;
		}
		i += 1;
	}
}

void	d_print_path(t_edge **path, t_graph g)
{
	int		i;

	i = 0;
	ft_printf("%s --> ", g.adj_list[g.source.index]->name);
	while (path[i])
	{
		if (path[i + 1])
		{
			d_print_node(g.adj_list[path[i]->to]);
			ft_fprintf(2, " --> ");
		}
		else
			d_print_node(g.adj_list[path[i]->to]);
		i++;
	}
}

void	d_print_nodes(t_graph special)
{
	for (int i = 0; i < special.adj_vert; i++)
	{
		d_print_node(special.adj_list[i]);
		ft_printf("@%d", special.adj_list[i]->nb_links);
		if (i + 1 < special.adj_vert) ft_printf(" - ");
	}
	ft_putendl(0);
	ft_putendl(0);
}

t_edge	*spe_add_edge(t_graph *g, int src, int dst)
{
	t_edge	*e;

	e = malloc(sizeof(t_edge));
	e->flow = 0;
	e->from = src;
	e->to = dst;
	e->capacity = 2147483647;
	e->rev = NULL;

	g->adj_list[src]->links[g->adj_list[src]->nb_links++] = e;
	g->adj_list[src]->links[g->adj_list[src]->nb_links] = NULL;
	return (e);
}

void	delete_edge(t_graph *g, int src, int dst)
{
	t_node *curr;

	curr = g->adj_list[src];
	for (int j = 0; j < curr->nb_links; j++)
	{
		if (curr->links[j])
		{
			if (curr->links[j]->to == dst)
			{
				curr->links[j] = NULL;
				break ;
			}
		}
	}

	curr = g->adj_list[dst];
	for (int j = 0; j < curr->nb_links; j++)
	{
		if (curr->links[j])
		{
			if (curr->links[j]->to == src)
			{
				curr->links[j] = NULL;
				break ;
			}
		}
	}

}

void	redo_graph(t_env env, t_graph *g, t_graph *special)
{
	int i;

	init_graph(special, g->adj_vert * 2 + 1);
	i = 0;
	while (i < g->adj_vert)
	{
		if (i == g->source.index || i == g->sink.index)
		{
			if (i == g->source.index)
				special->source.index = special->adj_vert;
			else
				special->sink.index = special->adj_vert;
			g->adj_list[i]->in_node = special->adj_vert;
			g->adj_list[i]->out_node = special->adj_vert;
			append_node(special, create_node(g->adj_list[i]->name));
			i += 1;
			continue;
		}
		t_node	*v_in = create_node(g->adj_list[i]->name);
		v_in->prev_index = i;
		v_in->type |= 1; //01

		t_node	*v_out = create_node(g->adj_list[i]->name);
		v_out->prev_index = i;
		v_out->type |= 2; //10
		int curr_index = special->adj_vert; // so curr_index would be the index of v_in and curr_index + 1 would be the one of v_out
		// is have to add an edge from curr_index to curr_index + 1

		t_edge	*un = malloc(sizeof(t_edge));
		un->to = curr_index + 1;
		un->from = curr_index;
		un->flow = 0;
		un->capacity = 1;
		un->rev = NULL; // somehow i have to deal with this shit FIXME

		v_in->links = malloc(sizeof(t_edge *) * (g->adj_vert * 2)); // we shouldn't have more than one edge here
		v_in->links[v_in->nb_links++] = un;
		v_in->links[v_in->nb_links] = NULL;

		g->adj_list[i]->in_node = special->adj_vert;
		g->adj_list[i]->out_node = special->adj_vert + 1;
		append_node(special, v_in);
		append_node(special, v_out);
		i += 1;
	}

	// now I iterate through the nodes again, adding the edged where they should be.
	i = 0;
	while (i < special->adj_vert)
	{
		if ((special->adj_list[i]->type & 1) == 0)
		{
			special->adj_list[i]->links = malloc(sizeof(t_edge *) * special->adj_vert + 1);
			for (int z = 0; z < special->adj_vert; z++)
				special->adj_list[i]->links[z] = NULL;
		}
		++i;
	}

	i = 0;
	// handle start
	while (i < g->adj_list[g->source.index]->nb_links)
	{
		spe_add_edge(special, special->source.index, \
					g->adj_list[g->adj_list[g->source.index]->links[i]->to]->in_node);
		delete_edge(g, g->source.index, g->adj_list[g->source.index]->links[i]->to);
		i += 1;
	}
	i = 0;
	while (i < g->adj_vert)
	{
		t_node *curr = g->adj_list[i];
		if (i == g->source.index || i == g->sink.index)
		{
			i += 1;
			continue;
		}
		for (int j = 0; j < curr->nb_links; j++)
		{
			if (curr->links[j] != NULL)
			{
				t_edge	*e1 = spe_add_edge(special,\
							curr->out_node,\
							g->adj_list[curr->links[j]->to]->in_node);
				t_edge	*e2 = spe_add_edge(special,\
							g->adj_list[curr->links[j]->to]->out_node,\
							curr->in_node);
				e1->rev = e2;
				e2->rev = e1;
				delete_edge(g, i, curr->links[j]->to);
			}
		}
		i += 1;
	}
}

void	algo(t_env env, t_graph *g)
{
	t_graph	special;
	t_paths	*head;

	head = NULL;
	redo_graph(env, g, &special);
	part_one(env, &special);
	part_two(env, &special, &head);
	ft_printf("prev-number of nodes: %d new-number of nodes: %d\n", g->adj_vert, special.adj_vert);
	d_print_edges(env, &special);
	 if (head == NULL && ft_fprintf(2, "ERROR\n"))
		exit(EXIT_FAILURE);
	//d_print_edges(env, &special);
	//print_file(env.debug);
	g->nb_p = count_paths(head);
	d_print_paths(head, &special);
	//play(g, head, env.debug);
}
