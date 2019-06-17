/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalonso <nalonso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 17:45:47 by nalonso           #+#    #+#             */
/*   Updated: 2019/06/15 15:54:47 by nalonso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	free_paths(t_paths *head)
{
	t_paths *tmp;
	int		i;
	int		j;

	while (head)
	{
		tmp = head->next;
		free(head->path);
		i = 0;
		j = head->move[0]->len;
		while (i < j)
		{
			free(head->move[i]);
			i += 1;
		}
		free(head->move);
		free(head);
		head = tmp;
	}
}

void	bfs_init(t_bfs *bfs, int nodes)
{
	bfs->prev = gb_malloc(&g_gb, sizeof(t_edge *) * (nodes + 1));
	bfs->visited = gb_malloc(&g_gb, sizeof(int) * (nodes + 1));
	bfs->dist = gb_malloc(&g_gb, sizeof(int) * (nodes + 1));
	bfs->cost = gb_malloc(&g_gb, sizeof(int) * (nodes + 1));
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
				&& tmp->flow == 1
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
