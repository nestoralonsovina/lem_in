/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalonso <nalonso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 17:45:47 by nalonso           #+#    #+#             */
/*   Updated: 2019/05/29 11:51:31 by nalonso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	bfs_init(t_bfs *bfs, int nodes)
{
	bfs->prev = malloc(sizeof(t_edge *) * (nodes + 1));
	bfs->visited = malloc(sizeof(int) * (nodes + 1));
	bfs->dist = malloc(sizeof(int) * (nodes + 1));
	if (!bfs->prev || !bfs->visited || !bfs->dist)
	{
		ft_putendl_fd(ERROR_MALLOC, 2);
		exit(EXIT_FAILURE);
	}
}

void	bfs_free(t_bfs *bfs)
{
	free(bfs->visited);
	free(bfs->dist);
	free(bfs->prev);
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
		bfs->visited[i] = 0;
		i += 1;
	}
	bfs->visited[src] = 1;
	bfs->dist[src] = 0;
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
			if (bfs->visited[tmp->to] == 0 && !tmp->visited)
			{
				bfs->dist[tmp->to] = bfs->dist[tmp->from] + 1;
				bfs->prev[tmp->to] = tmp;
				bfs->q.push(&(bfs->q), tmp->to);
				bfs->visited[tmp->to] = 1;
			}
			i += 1;
		}
	}
	free(bfs->q.array);
}
