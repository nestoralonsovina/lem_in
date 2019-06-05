/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalonso <nalonso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 17:46:54 by nalonso           #+#    #+#             */
/*   Updated: 2019/06/02 16:02:32 by jallen           ###   ########.fr       */
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

	bfs->q = create_queue(nodes);
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

	ft_printf("searching for a path...\n");
	bfs_init(bfs, g->adj_vert);
	bfs_reset_struct(bfs, g->adj_vert, g->source.index);	// Initialize all the arrays to default values

	// Relax the edges repeatedly
	for (int z = 1; z < g->adj_vert - 1; z++)
	{
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
					bfs->cost[e->to] = bfs->cost[e->from] + w;
					bfs->dist[e->to] = bfs->dist[e->from] + 1;
					bfs->prev[e->to] = e;
				}
			}
		}
	}

	// check for negative-weight cycles
	/*
	for (int i = 0; i < g->adj_vert; i++)
	{
		for (size_t j = 0; j < g->adj_list[i]->nb_links; j++)
		{
			t_edge *e = g->adj_list[i]->links[j];
			int w = e->flow == 0 ? 1 : -1; // a edge would have a cost of 1 if it's the first time you go through it, -1 if you are going backwards
			if (bfs->cost[e->from] + w < bfs->cost[e->to])
			{
				ft_fprintf(2, "{r} graph contains a negative-weight cycle {R}\n");
			}
		}
	}
	*/
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

void	lets_have_fun(t_env env, t_graph *g, t_paths **head_ref)
{
	t_paths	*head;
	int		mf;
	t_bfs	bfs;

	mf = 0;
	head = NULL;
	while (1)
	{
		bellman_ford(env, g, &bfs);
		if (bfs.prev[g->sink.index] == NULL)
		{
			ft_fprintf(2, "Error: path not found\n");
			break ;
		}
		else
		{
			ford_fulkerson(env, g, &bfs);
			mf += 1;
		}
		// i should make a different array for weights and for distance, since i use the distance to create the paht array
		append_path(&head, new_path(make_path(bfs.prev, bfs.dist[g->sink.index], g->sink.index), 0));
	}
	*head_ref = head;
}

void	algo(t_env env, t_graph *g)
{
	t_paths	*head;

	head = NULL;
	lets_have_fun(env, g, &head);
	if (head == NULL && ft_fprintf(2, "ERROR\n"))
		exit(EXIT_FAILURE);
	d_print_paths(head, g);
	//print_file(env.debug);
	g->nb_p = count_paths(head);
	//play(g, head, env.debug);
}
