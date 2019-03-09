#include "../includes/lem_in.h"
#include <limits.h>

void		print_queue(t_queue *q);

static void	construct_path(t_graph *g, t_queue *q, int dst)
{
	size_t i;

	i = q->front;
	while (i < q->rear)
	{
		ft_printf("%s --> ", g->adj_list[q->array[i]]->name);
		i += 1;
	}
	ft_printf("%s\n", g->adj_list[dst]->name);
}

void		bfs(t_graph *g, int src, int dst)
{
	t_queue *q;
	int		*visited;

	visited = (int *)malloc(sizeof(int) * g->adj_vert);
	for (int i = 0; i < g->adj_vert; i++)
	{
		visited[i] = 0;
	}
	q = create_queue(g->adj_vert);
	enqueue(q, src);

	visited[src] = 1;
	while (q->size != 0)
	{
		int v = dequeue(q);
		if (v == dst)
		{
			construct_path(g, q, dst);
		}

		for (size_t w = 0; w < g->adj_list[v]->nb_links; w++)
		{
			if (visited[g->adj_list[v]->links[w]] == 0)
			{
				enqueue(q, g->adj_list[v]->links[w]);
				visited[g->adj_list[v]->links[w]] = 1;
			}
		}
	}
	//print_queue(q);
}

# define White 0
# define Gray 1
# define Black 2

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

void	bfs_oreilly(t_graph *g, int src, int dst)
{
	int		i;
	int		*visited;
	int		*pred;
	int		*dist;
	t_queue	*q;

	i = 0;
	q = create_queue(g->adj_vert);
	visited = malloc(sizeof(int) * g->adj_vert);
	pred = malloc(sizeof(int) * g->adj_vert);
	dist = malloc(sizeof(int) * g->adj_vert);
	while (i < g->adj_vert)
	{
		pred[i] = -1;
		dist[i] = INT_MAX;
		visited[i] = White;
		i += 1;
	}

	dist[src] = 0;
	visited[src] = Gray;
	enqueue(q, src);
	//ft_putendl("Where are you baby");
	while (q->size != 0)
	{
		int u = dequeue(q);
		//ft_printf("Number of neighbours: %d\n", g->adj_list[u]->nb_links);
		for (size_t neighbour = 0; neighbour < g->adj_list[u]->nb_links; neighbour++)
		{
			//ft_printf("neighbour: %d of u: %d ", neighbour, u);
			int v = g->adj_list[u]->links[neighbour];
			//ft_printf("v: %d\n", v);
			if (visited[v] == White)
			{
				dist[v] = dist[u] + 1;
				pred[v] = u;
				visited[v] = Gray;
				enqueue(q, v);
			}
		}
		visited[u] = Black;
	}
	/*
	for (int i = 0; i < g->adj_vert; i++)
	{
		ft_printf("i: %d - %d %d\n", i, dist[i], pred[i]);
	}
	ft_putendl(0);
	*/
	print_path(g, pred, dst);
}
