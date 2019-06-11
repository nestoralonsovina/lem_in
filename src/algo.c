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
				&& tmp->flow != 0
				&& g->adj_list[tmp->to]->blocked == 0)
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

void	bellman_ford(t_env e, t_graph *g, t_bfs *bfs)
{

	// This implementation takes in a graph, represented as lists of vertices and edges,
	// and fills two arrays (distance and predecessor) about the shortest patH From the source to each vertex

	bfs_init(bfs, g->adj_vert);
	bfs_reset_struct(bfs, g->adj_vert, g->source.index);	// Initialize all the arrays to default values

	// Relax the edges repeatedly
	for (int z = 1; z < g->adj_vert - 1; z++)
	{
		int is_any_weight_updated = 0;
		for (int i = 0; i < g->adj_vert; i++)
		{
			for (size_t j = 0; j < g->adj_list[i]->nb_links; j++)
			{
				t_edge *e = g->adj_list[i]->links[j];
				int w = e->flow == 0 ? 1 : -1; // a edge would have a cost of 1 if it's the first time you go through it, -1 if you are going backwards
				if ((e->flow == 0 || e->flow == -1) \
					&& e->to != g->source.index \
					&& bfs->cost[e->from] != 2147483647 \
					&& bfs->cost[e->from] + w < bfs->cost[e->to])
				{
					is_any_weight_updated = 1;
					bfs->cost[e->to] = bfs->cost[e->from] + w;
					bfs->dist[e->to] = bfs->dist[e->from] + 1;
					bfs->prev[e->to] = e;
				}
			}
		}
		if (!is_any_weight_updated)
			break ;
	}
}

/*
**	Full information: https://en.wikipedia.org/wiki/Ford-Fulkerson_algorithm
**	Ford-fulkerson is a greedy algorithm that computes the maximum flow in a
**	flow network. The method to find the augmenting path is not defined, we're
**	using bellman-ford to do that.
*/

void	ford_fulkerson(t_env e, t_graph *g, t_bfs *bfs)
{
	for (t_edge *e = bfs->prev[g->sink.index]; e != NULL; e = bfs->prev[e->from])
	{
		e->flow += 1;
		e->rev->flow -=1;
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
			if (tmp_path[i]->to != g->sink.index)
				g->adj_list[tmp_path[i]->to]->blocked = 1;
			i += 1;
		}
		append_path(&head, new_path(tmp_path, 0));
	}
	bfs_free(&bfs);
	*head_ref = head;
}

void	d_print_edges(t_env env, t_graph *g)
{
	int i;
	int j;

	i = 0;
	while (i < g->adj_vert)
	{
		j = 0;
		ft_printf("node %s:\n", g->adj_list[i]->name);
		while (j < g->adj_list[i]->nb_links)
		{
			ft_printf("\t%d --> %d @ %d\n", g->adj_list[i]->links[j]->from, g->adj_list[i]->links[j]->to, g->adj_list[i]->links[j]->flow);
			j += 1;
		}
		i += 1;
	}
}

void	d_print_nodes(t_graph special)
{
	for (int i = 0; i < special.adj_vert; i++)
	{
		ft_printf("%s", special.adj_list[i]->name);
		if (special.adj_list[i]->type & 1)
		{
			ft_printf("_IN");
		}
		else if (special.adj_list[i]->type & 2)
		{
			ft_printf("_OUT");
		}
		ft_printf("@%d", special.adj_list[i]->nb_links);
		if (i + 1 < special.adj_vert) ft_printf(" - ");
	}
	ft_putendl(0);
	ft_putendl(0);
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
				special->source.index = i;
			else
				special->sink.index = i;
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

		v_in->links = malloc(sizeof(t_edge) + 1); // we shouldn't have more than one edge here
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
			special->adj_list[i]->links = malloc(sizeof(t_edge *) * special->adj_vert);
			for (int z = 0; z < special->adj_vert; z++)
				special->adj_list[i]->links[z] = NULL;
		}
		++i;
	}

	i = 0;
	while (i < g->adj_vert)
	{
		t_node *curr = g->adj_list[i];
		int j = 0;
		while (j < curr->nb_links)
		{
			t_node *go_to = g->adj_list[curr->links[j]->to];
			if (special->adj_list[go_to->in_node]->type != 0)
				add_edge(special, curr->out_node, go_to->in_node);
			j++;
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
	part_one(env, g);
	part_two(env, g, &head);
	ft_printf("prev-number of nodes: %d new-number of nodes: %d\n", g->adj_vert, special.adj_vert);
	d_print_nodes(*g);
	d_print_nodes(special);
	d_print_edges(env, &special);
	if (head == NULL && ft_fprintf(2, "ERROR\n"))
		exit(EXIT_FAILURE);
	//d_print_edges(env, &special);
	print_file(env.debug);
	g->nb_p = count_paths(head);
	head = trim_paths(head, g);
	play(g, head, env.debug);
}
