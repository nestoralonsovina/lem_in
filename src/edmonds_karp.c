#include "../includes/lem_in.h"
#include <limits.h>

void	print_path(t_graph *g)
{
	int i = g->adj_vert - 1;

	while (i != -1)
	{
		if (g->pred[i] != -1)
			ft_printf("%s <-- ", g->adj_list[i]->name);
		else
			ft_printf("%s\n", g->adj_list[i]->name);
		i = g->pred[i];
	}
}

void	print_matrix(t_graph *g)
{
	for (int v = 0; v < g->adj_vert; v++) {
		for (int w = 0; w < g->adj_vert; w++) {
			ft_printf("%3d", g->flow[v][w]);
		}
		ft_printf("\n");
	}
}

typedef struct	s_path
{
	int 		nb_ant;
	t_node		*n;
	struct s_path *next;
}				t_path;

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

int 	aumenting_path(t_graph *g, int src, int dst)
{
	t_queue	*q;
	int 	i;

	// create circular queue
	q = create_queue(g->adj_vert);
	enqueue(q, src);

	// restart visited and pred arrays
	i = 0;
	while (i < g->adj_vert)
	{
		g->pred[i] = -1;
		g->visited[i] = 0;
		i += 1;
	}

	// initialize previous and visited to start loop
	g->pred[src] = -1;
	g->visited[src] = 1;

	while (q->size != 0)
	{
		int u = front(q);
		int n = g->adj_list[u]->nb_links;

		for (int ngb = 0; ngb < n; ngb++)
		{
			int v = g->adj_list[u]->links[ngb];
			if (v == u || g->visited[v] != 0)
				continue;
			if (g->flow[u][v] < 1)
			{
				enqueue(q, v);
				g->visited[v] = 1;
				g->pred[v] = u;
			}
		}
		dequeue(q);
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

int		edmonds_karp(t_graph *g, int src, int dst)
{
	int max_flow;
	int ret;

	create_matrix(g, g->adj_vert);
	g->pred = malloc(sizeof(int) * g->adj_vert);
	g->visited = malloc(sizeof(int) * g->adj_vert);
	max_flow = 0;
	ret = aumenting_path(g, src, dst);
	while (ret == 1)
	{
		max_flow += process_path(g, dst);
		print_path(g);
		ret = aumenting_path(g, src, dst);
	}
	return (max_flow);
}