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

int		algo_manage_path(t_bfs *bfs, t_graph *g, t_paths **head, int bg)
{
	t_edge	**tmp_path;
	double	last;

	tmp_path = make_path(bfs->prev, bfs->dist[g->sink.index], g->sink.index);
	if (bg)
	{
		path_goes_backwards(*head, tmp_path);
	}
	else
		append_path(head, new_path(tmp_path, bg));
	last = calculate_ants(*head, g);
	if (last <= 0)
	{
		return (0);
	}
	return (1);
}

void	adjust_flow(t_graph *g, t_env *env, t_bfs bfs)
{
	t_edge	*e;

	e = bfs.prev[g->sink.index];
	while (e != NULL)
	{
		e->flow = e->flow + 1;
		e->rev->flow = e->rev->flow - 1;
		if (e->flow == 0 && e->rev->flow == 0)
			env->bg = 1;
		e = bfs.prev[e->from];
	}
}

void	find_paths(t_env env, t_graph *g, t_paths **head_ref)
{
	t_paths	*head;
	t_bfs	bfs;

	head = *head_ref;
	bfs_init(&bfs, g->adj_vert);
	env.bg = 0;
	while (42)
	{
		bfs_reset_struct(&bfs, g->adj_vert, g->source.index);
		bfs_run_iteration(&bfs, g);
		if (bfs.prev[g->sink.index] == NULL)
			break ;
		env.bg = 0;
		adjust_flow(g, &env, bfs);
		if (algo_manage_path(&bfs, g, &head, env.bg) == 0)
			break ;
	}
	bfs_free(&bfs);
	*head_ref = head;
}

void	manage_extra_paths(t_env env, t_graph *g, t_paths **head)
{
	t_paths *tmp;
	int		cnt;

	tmp = *head;
	cnt = 0;
	while (tmp)
	{
		if (tmp->bg)
		{
			find_paths(env, g, head);
			cnt = 0;
		}
		cnt++;
		tmp = tmp->next;
	}
}

void	algo(t_env env, t_graph *g)
{
	t_paths	*head;

	head = NULL;
	find_paths(env, g, &head);
	manage_extra_paths(env, g, &head);
	if (head == NULL && ft_fprintf(2, "ERROR\n"))
		exit(EXIT_FAILURE);
	print_file(env.debug);
	g->nb_p = count_paths(head);
	head = trim_paths(head, g);
	head = delete_superposition(head, g);
	head = trim_paths(head, g);
	play(g, head, env.debug);
	free_paths(head);
}
