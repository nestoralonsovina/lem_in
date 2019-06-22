/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalonso <nalonso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 15:31:29 by nalonso           #+#    #+#             */
/*   Updated: 2019/06/22 15:38:26 by nalonso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	reset_blocked(t_graph *sp)
{
	int	i;

	i = 0;
	while (i < sp->adj_vert)
		sp->adj_list[i++]->blocked = 0;
}

static void	search_paths(t_graph *g, t_paths **head_ref)
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

int			save_paths(t_env *env, t_graph *sp)
{
	t_paths *last_paths;
	t_paths	*ptr;

	last_paths = NULL;
	search_paths(sp, &last_paths);
	reset_blocked(sp);
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
				return (0);
			}
			last_paths = last_paths->next;
		}
		last_paths = ptr;
	}
	env->paths[env->curr_nb_paths++] = last_paths;
	return (1);
}
