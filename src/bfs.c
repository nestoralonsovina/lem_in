#include "../includes/lem_in.h"
#include "../includes/queue.h"
#include <limits.h>

void	bfs_oreilly(t_graph *g, int src, int ants)
{
	int		i;
	int		*visited;
	int		*pred;
	int		*dist;
	t_queue	q;

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

	while (q.size != 0)
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
}
