/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalonso <nalonso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 17:46:54 by nalonso           #+#    #+#             */
/*   Updated: 2019/06/22 15:35:44 by nalonso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

static void	visit_children(t_graph *g, t_bfs *bfs, int cur)
{
	t_edge	*e;
	size_t	j;

	j = 0;
	e = NULL;
	while (j < g->adj_list[cur]->nb_links)
	{
		e = g->adj_list[cur]->links[j++];
		if (e->capacity - e->flow > 0 && e->to != g->source.index)
		{
			if (bfs->cost[e->from] + 1 < bfs->cost[e->to])
			{
				bfs->cost[e->to] = bfs->cost[e->from] + 1;
				bfs->dist[e->to] = bfs->dist[e->from] + 1;
				bfs->prev[e->to] = e;
				bfs->q.push(&bfs->q, e->to);
			}
		}
	}
}

void		bellman_ford(t_graph *g, t_bfs *bfs)
{
	t_edge	*e;
	int		cur;

	bfs_init(bfs, g->adj_vert);
	bfs_reset_struct(bfs, g->adj_vert, g->source.index);
	while (bfs->q.size != 0)
	{
		cur = bfs->q.pop(&(bfs->q));
		if (g->adj_list[cur]->incoming)
		{
			e = g->adj_list[cur]->incoming;
			if (bfs->cost[e->to] - 1 < bfs->cost[e->from] \
				&& e->from != g->source.index && bfs->prev[e->from] == NULL)
			{
				bfs->cost[e->from] = bfs->cost[e->to] - 1;
				bfs->dist[e->from] = bfs->dist[e->to] + 1;
				bfs->prev[e->from] = e;
				bfs->q.push(&bfs->q, e->from);
			}
		}
		visit_children(g, bfs, cur);
		if (bfs->prev[g->sink.index] != NULL)
			break ;
	}
	free(bfs->q.array);
}

void		ford_fulkerson(t_graph *g, t_bfs *bfs)
{
	t_edge	*e;

	e = bfs->prev[g->sink.index];
	while (e != NULL)
	{
		if (bfs->prev[e->from] != e)
		{
			g->adj_list[e->to]->incoming = e;
			g->adj_list[e->from]->incoming = NULL;
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

void		part_one(t_env *env, t_graph *g)
{
	int		mf;
	t_bfs	bfs;

	mf = 0;
	bfs_init(&bfs, g->adj_vert);
	while (1)
	{
		bellman_ford(g, &bfs);
		if (bfs.prev[g->sink.index] == NULL)
		{
			break ;
		}
		else
		{
			ford_fulkerson(g, &bfs);
			if (!save_paths(env, g))
				break ;
			mf += 1;
		}
	}
}

void		algo(t_env env, t_graph *g)
{
	t_graph	special;
	t_paths	*head;

	head = NULL;
	redo_graph(g, &special);
	env.curr_nb_paths = 0;
	env.paths = gb_malloc(&g_gb, sizeof(t_paths *) * g->adj_vert + 1);
	env.best_iteration = -1;
	part_one(&env, &special);
	if (env.best_iteration != -1 && env.curr_nb_paths)
		head = env.paths[env.best_iteration];
	else if (env.curr_nb_paths)
		head = env.paths[env.curr_nb_paths - 1];
	if (head == NULL && ft_fprintf(2, "ERROR\n"))
		exit(EXIT_FAILURE);
	g->nb_p = count_paths(head);
	print_file(env.debug);
	head = trim_paths(head, g);
	play(g, head, env.debug);
	free_graph(&special);
}
