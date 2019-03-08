#include "../includes/lem_in.h"
#include <limits.h>

void		print_queue(t_queue *q);

void		bfs(t_graph *g, int src, size_t dst)
{
	t_queue *q;
	int		*visited;

	(void)dst;
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

		for (size_t w = 0; w < g->adj_list[v]->nb_links; w++)
		{
			if (visited[g->adj_list[v]->links[w]] == 0)
			{
				enqueue(q, g->adj_list[v]->links[w]);
				visited[g->adj_list[v]->links[w]] = 1;
			}
		}
		print_queue(q);
	}
}
