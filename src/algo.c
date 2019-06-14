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

void	bellman_ford(t_env env, t_graph *g, t_bfs *bfs)
{
	bfs_init(bfs, g->adj_vert);
	bfs_reset_struct(bfs, g->adj_vert, g->source.index);

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
				}
			}
		}
		if (bfs->prev[g->sink.index] != NULL)
			break ;
	}
	free(bfs->q.array);
}

void	ford_fulkerson(t_env e, t_graph *g, t_bfs *bfs)
{
	for (t_edge *e = bfs->prev[g->sink.index]; e != NULL;) 
	{
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

void	search_paths(t_env e, t_graph *g, t_paths **head_ref)
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

void	save_paths(t_env *env, t_graph *sp, t_paths **head_ref)
{
	t_paths *last_paths = NULL;

	search_paths(*env, sp, &last_paths);
	for (int i = 0; i < sp->adj_vert; i++)
	{
		sp->adj_list[i]->blocked = 0;
	}
	transform_paths(*env, sp, &last_paths);
	calculate_ants(last_paths, &env->graph);
	if (env->best_iteration == -1)
	{
		t_paths *ptr = last_paths;
		while (last_paths)
		{
			if (last_paths->predicted_ants <= 0)
			{
				env->best_iteration = env->curr_nb_paths - 1;
			}
			last_paths = last_paths->next;
		}
		last_paths = ptr;
	}

	env->paths[env->curr_nb_paths++] = last_paths;
}

void	part_one(t_env *env, t_graph *g, t_paths **head_ref)
{
	int		mf;
	t_bfs	bfs;

	mf = 0;
	bfs_init(&bfs, g->adj_vert);
	while (1)
	{
		bellman_ford(*env, g, &bfs);
		if (bfs.prev[g->sink.index] == NULL)
		{
			break ;
		}
		else
		{
			ford_fulkerson(*env, g, &bfs);
			save_paths(env, g, head_ref);
			mf += 1;
		}
	}
	bfs_free(&bfs);
}


void	algo(t_env env, t_graph *g)
{
	t_graph	special;
	t_paths	*head;

	head = NULL;
	redo_graph(env, g, &special);
	env.curr_nb_paths = 0;
	env.paths = malloc(sizeof(t_paths *) * g->adj_vert + 1);
	env.best_iteration = -1;
	part_one(&env, &special, &head);
	if (env.best_iteration != -1)
	{
		head = env.paths[env.best_iteration];
	}
	else
	{
		head = env.paths[env.curr_nb_paths - 1];
	}
	 if (head == NULL && ft_fprintf(2, "ERROR\n"))
		exit(EXIT_FAILURE);
	g->nb_p = count_paths(head);
	print_file(env.debug);
	head = trim_paths(head, g);
	play(g, head, env.debug);
}
