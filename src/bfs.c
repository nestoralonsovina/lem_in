#include "../includes/lem_in.h"
#include <limits.h>

void		print_queue(t_queue *q);

void	print_path(t_graph *g, int *pred, int dst)
{
	int i = dst;

	while (i != -1)
	{
		if (pred[i] != -1)
			ft_printf("%s <-- ", g->adj_list[i]->name);
		else
			ft_printf("%s\n", g->adj_list[i]->name);
		i = pred[i];
	}
}

void	bfs_oreilly(t_graph *g, int src, int ants)
{
	int		i;
	int		*visited;
	int		*pred;
	int		*dist;
	t_queue	*q;

	(void)ants;
	i = 0;
	q = create_queue(g->adj_vert);
	visited = malloc(sizeof(int) * g->adj_vert);
	pred = malloc(sizeof(int) * g->adj_vert);
	dist = malloc(sizeof(int) * g->adj_vert);
	while (i < g->adj_vert)
	{
		pred[i] = -1;
		dist[i] = INT_MAX;
		visited[i] = 0;
		i += 1;
	}

	dist[src] = 0;
	visited[src] = 1;
	enqueue(q, src);

	while (q->size != 0)
	{
		int u = dequeue(q);

		for (size_t neighbour = 0; neighbour < g->adj_list[u]->nb_links; neighbour++)
		{
			int v = g->adj_list[u]->links[neighbour];

			if (visited[v] == 0)
			{
				dist[v] = dist[u] + 1;
				pred[v] = u;
				visited[v] = 1;
				enqueue(q, v);
			}
		}
	}
	print_path(g, pred, g->adj_vert - 1);
}