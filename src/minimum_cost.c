#include "../includes/lem_in.h"
#include "../includes/binary_heap.h"
#include <limits.h>

// minimal augmenting path
void	dijkstra(t_graph *g, int src, int dst)
{
	t_binary_heap pq;
	int 	i;

	i = 0;
	pq = bh_init(g->adj_vert);
	while (i < g->adj_vert)
	{
		g->pred[i] = -1;
		g->dist[i] = INT_MAX;
		i += 1;
	}

	g->dist[src] = 0;
	i = 0;
	while (i < g->adj_vert)
	{
		pq.insert(&pq, i, g->dist[i]);
		i += 1;
	}

	// main loop
	while (!pq.is_empty(&pq))
	{
		int u, t;

		u = pq.smallest(&pq);
		t = 0;
		if (u == dst)
			return ;

		for (int ngb = 0; ngb < g->adj_list[u]->nb_links; ngb++)
		{
			int v = g->adj_list[u]->links[ngb];

		}

	}

}

int 	minimum_cost(t_graph *g, int src, int dst)
{

}
