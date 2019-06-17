/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalonso <nalonso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 17:46:54 by nalonso           #+#    #+#             */
/*   Updated: 2019/06/15 15:52:31 by nalonso          ###   ########.fr       */
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
		if (e->capacity - e->flow > 0)
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

void	bellman_ford(t_env env, t_graph *g, t_bfs *bfs)
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
			if (bfs->cost[e->to] - 1 < bfs->cost[e->from])
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

void	ford_fulkerson(t_env env, t_graph *g, t_bfs *bfs)
{
	t_edge	*e;

	e = bfs->prev[g->sink.index];
	while (e != NULL)
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
	t_edge	**tmp_path;
	int		i;

	bfs_init(&bfs, g->adj_vert);
	head = NULL;
	while (1)
	{
		bfs_reset_struct(&bfs, g->adj_vert, g->source.index);
		bfs_run_iteration(&bfs, g);
		if (bfs.prev[g->sink.index] == NULL)
			break ;
		tmp_path = make_path(bfs.prev, bfs.dist[g->sink.index], g->sink.index);
		i = 0;
		while (i < plen(tmp_path))
		{
			if (tmp_path[i]->to != g->sink.index)
				g->adj_list[tmp_path[i]->to]->blocked = 1;
			i += 1;
		}
		append_path(&head, new_path(tmp_path, 0));
	}
	*head_ref = head;
}

void	save_paths(t_env *env, t_graph *sp, t_paths **head_ref)
{
	t_paths *last_paths;
	t_paths	*ptr;
	int		i;

	last_paths = NULL;
	i = 0;
	search_paths(*env, sp, &last_paths);
	while (i < sp->adj_vert)
		sp->adj_list[i++]->blocked = 0;
	transform_paths(*env, sp, &last_paths);
	calculate_ants(last_paths, &env->graph);
	if (env->best_iteration == -1)
	{
		ptr = last_paths;
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
}

void	algo(t_env env, t_graph *g)
{
	t_graph	special;
	t_paths	*head;

	head = NULL;
	redo_graph(env, g, &special);
	env.curr_nb_paths = 0;
	env.paths = gb_malloc(&g_gb, sizeof(t_paths *) * g->adj_vert + 1);
	env.best_iteration = -1;
	part_one(&env, &special, &head);
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
