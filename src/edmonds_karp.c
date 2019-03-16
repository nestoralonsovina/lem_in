#include "../includes/lem_in.h"
#include "../includes/queue.h"
#include <limits.h>

void	create_matrix(t_graph *g, int n)
{
	int 	i;
	int 	j;

	i = 0;
	g->flow = malloc(sizeof(int *) * n);
	while (i < n)
	{
		g->flow[i] = malloc(sizeof(int) * n);
		j = 0;
		while (j < n)
		{
			g->flow[i][j] = 0;
			j += 1;
		}
		i += 1;
	}
}

int 	augmenting_path(t_graph *g, int src, int dst)
{
	t_queue	q;
	int 	i;

	// create circular queue
	q = create_queue(g->adj_vert);
	q.push(&q, src);

	// restart visited and pred arrays
	i = 0;
	while (i < g->adj_vert)
	{
		g->pred[i] = -1;
		g->dist[i] = INT_MAX;
		g->visited[i] = 0;
		i += 1;
	}

	// initialize previous and visited to start loop
	g->dist[src] = 0;
	g->pred[src] = -1;
	g->visited[src] = 1;

	while (q.size != 0)
	{
		int u = q.front(&q);
		int n = g->adj_list[u]->nb_links;

		for (int ngb = 0; ngb < n; ngb++)
		{
			int v = g->adj_list[u]->links[ngb];
			if (v == u || g->visited[v] != 0)
				continue;
			if (g->flow[u][v] < 1)
			{
				q.push(&q, v);
				g->dist[v] = g->dist[u] + 1;
				g->visited[v] = 1;
				g->pred[v] = u;
			}
		}
		q.pop(&q);
	}
	return (g->visited[dst] != 0);
}

int 	process_path(t_graph *g, int dst)
{
	int v = dst;

	int increment = 1;

	while (g->pred[v] != -1)
	{
		g->flow[g->pred[v]][v] += increment;
		g->flow[v][g->pred[v]] -= increment;

		v = g->pred[v];
	}

	return (increment);
}

int		edmonds_karp(t_env *env, t_graph *g, int src, int dst)
{
	int max_flow;
	int ret;

	create_matrix(g, g->adj_vert);
	g->pred = malloc(sizeof(int) * g->adj_vert);
	g->dist = malloc(sizeof(int) * g->adj_vert);
	g->visited = malloc(sizeof(int) * g->adj_vert);
	max_flow = 0;
	ret = augmenting_path(g, src, dst);
	while (ret == 1)
	{
		max_flow += process_path(g, dst);
		ret = augmenting_path(g, src, dst);
	}
	return (max_flow);
}
