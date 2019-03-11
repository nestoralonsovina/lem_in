#include "../includes/lem_in.h"
#include <limits.h>

int 	**flow;
int 	*pred;

void	print_path(t_graph *g, int *pred, int dst);

void	create_matrix(int rows, int cols)
{
	int 	i;

	i = 0;
	flow = malloc(sizeof(int *) * rows);
	while (i < rows)
	{
		flow[i] = malloc(sizeof(int *) * cols);
		ft_bzero(flow[i], cols);
		i += 1;
	}
}

int 	aumenting_path(t_graph *g, int src, int dst)
{
	t_queue	*q;
	int 	*visited;

	// allocate
	visited = malloc(sizeof(int) * g->adj_vert);

	// create circular queue
	q = create_queue(g->adj_vert);
	enqueue(q, src);

	// initialize previous and visited to start loop
	pred[src] = -1;
	visited[src] = 1;

	while (q->size != 0)
	{
		int u = front(q);
		int n = g->adj_list[u]->nb_links;

		for (int ngb = 0; ngb < n; ngb++)
		{
			int v = g->adj_list[u]->links[ngb];
			if (v == u || visited[v] != 0)
				continue;
			if (flow[u][v] < 1)
			{
				enqueue(q, v);
				visited[v] = 1;
				pred[v] = u;
			}
		}
		dequeue(q);
	}
	return (visited[dst] != 0);
}

int 	process_path(int dst)
{
	int v = dst;

	int increment = 1;

	// push minimal increment over the path
	v = dst;
	while (pred[v] != -1)
	{
		flow[pred[v]][v] += increment;
		flow[v][pred[v]] -= increment;

		v = pred[v];
	}

	return (increment);
}

int		edmonds_karp(t_graph *g, int src, int dst)
{
	int max_flow;

	pred = malloc(sizeof(int) * g->adj_vert);
	max_flow = 0;
	create_matrix(g->adj_vert, g->adj_vert);
	while (aumenting_path(g, src, dst))
	{
		max_flow += process_path(dst);
	}
	return (max_flow);
}