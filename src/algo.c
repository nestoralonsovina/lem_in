#include "../includes/lem_in.h"
#include <limits.h>
#include <stdbool.h>

static void p_array(int *a, int l) {
	for (int i = 0; i < l; i++) ft_printf("%d ", a[i]);
	ft_putendl(0);
}

static int len(t_edge **a) {
	int i = 0;
	while (a[i])
		i++;
	return i;
}

static void d_print_path(t_edge **path, t_graph g) {
	int i = 0;


	ft_printf("%s --> ", g.adj_list[g.source.index]->name);
	while (path[i]) {
		if (path[i + 1])
			ft_printf("%s --> ", g.adj_list[path[i]->to]->name);
		else
			ft_printf("%s\n", g.adj_list[path[i]->to]->name);
		i++;
	}
}

static t_edge **make_path(t_edge **prev, int l, int d)
{
	t_edge **path = malloc(sizeof(t_edge *) * (l + 1));
	path[l--] = NULL;
	for (t_edge *e = prev[d]; e != NULL; e = prev[e->from]) {
		path[l--] = e;
	}
	return path;

}

void	algo(t_env env, t_graph g)
{

	// n -> number of nodes, s -> index of source, d -> index of destination
	int n = g.adj_vert;
	int s = g.source.index;
	int d = g.sink.index;

	// iterators
	int		i; 
	int		cur; 
	t_edge	*tmp;

	// saved paths
	t_edge  **tmp_path;
	t_paths *head = NULL;

	while (true)
	{

		// create a queue for the BFS
		t_queue q = create_queue(n);

		// basic arrays for each bfs iterations
		t_edge *prev[n];
		int dist[n];
		int visited[n];

		// set default values
		i = 0;
		while (i < n)
		{
			prev[i] = NULL;
			dist[i] = INT_MAX;
			visited[i] = false;
			i += 1;
		}

		// whitelist source

		visited[s] = 1;
		dist[s] = 0;
		q.push(&q, s);

		// run BFS
		while (q.size != 0)
		{

			cur = q.pop(&q);

			i = 0;
			while (i < g.adj_list[cur]->nb_links)
			{
				tmp = g.adj_list[cur]->links[i];
				if (visited[tmp->to] == 0)
				{
					dist[tmp->to] = dist[tmp->from] + 1;
					prev[tmp->to] = tmp;
					q.push(&q, tmp->to);
					visited[tmp->to] = true;
				}
				i += 1;
			}
		} // end of BFS

		// exit the loop if no path was found in the last iteration of BFS
		if (prev[d] == NULL)
		{
			break;
		}

		// BFS succedd, save path into list
		tmp_path = make_path(prev, dist[d], d);
		if (env.debug)
		{
			d_print_path(tmp_path, g);
		}

		/*
		** Since this is not EK or a network flow algorithm I'll describe what
		** values I'll be asigning to the different parameters.\
		**
		** Maximum flow: number of paths found up to this momment
		** Minimum cost: length of the path
		** Time: same computation as always -> time := (ants / maxFlow) + minimumCost
		**
		** The idea is that each path will have this three values, and the I'll take
		** the combination of paths that minimize the time based on the maximum flow
		** -> (paths combining) and the minimum cost -> (lenght of the paths being 
		** combined.
		*/ 



	} // end of MAIN loop

}
