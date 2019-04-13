#include "../includes/lem_in.h"
#include <limits.h>

static int	ft_min(int a, int b) {
	return (a > b ? b : a);
}

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

static int compute_time(t_graph *g, int mf, int mc) {
	return ((g->nb_ant / mf) + mc);
}

static void d_print_path(t_edge **path) {
	int i = 0;

	while (path[i]) {
		if (path[i + 1])
			ft_printf("%d --> ", path[i]->to);
		else
			ft_printf("%d\n", path[i]->to);
		i++;
	}
}

/*
 ** Use the Bellman-Ford algorithm (which work with negative edge weight) to
 ** find an augmenting path through the flow network
 */

t_edge		**bellman_ford(t_graph *g) {
	int n = g->adj_vert;
	int s = g->source.index;
	int d = g->sink.index;

	int dist[n];
	t_edge **prev = malloc(sizeof(t_edge *) * n);

	for (int i = 0; i < n; i++) {
		dist[i] = INT_MAX;
		prev[i] = NULL; 
	}

	dist[s] = 0;
	for (int i = 0; i < n - 1; i++) { //relax all the edges repeatedly
		for (int j = 0; j < n; j++) { // iterate through the vertices
			for (int e = 0; e < g->adj_list[j]->nb_links; e++) { // iterate through the edges of each vertice
				t_edge *edge = g->adj_list[j]->links[e];

				if (dist[edge->from] != INT_MAX && dist[edge->from] + edge->cost < dist[edge->to] && (edge->cap - edge->flow) > 0) {
					dist[edge->to] = dist[edge->from] + edge->cost;
					prev[edge->to] = edge;
				}
			}
		}
	}

	if (!prev[d])
		return NULL;

	//p_array(dist, n);
	int l = dist[d];
	t_edge **path = malloc(sizeof(t_edge *) * (l + 1));
	path[l--] = NULL;
	for (t_edge *e = prev[d]; e != NULL; e = prev[e->from]) {
		path[l--] = e;
	}
	return path;
}

int			min_cost_max_flow_with_bellman_ford(t_graph g) {

	t_edge **path;
	int minCost = 0;
	int maxFlow = 0;

	path = bellman_ford(&g);
	while (path != NULL) {
		int bottleNeck = INT_MAX;
		for (int i = 0; i < len(path); i++) {
			t_edge *edge = path[i];
			bottleNeck = ft_min(bottleNeck, edge->cap - edge->flow);
		}

		for (int i =0; i < len(path); i++) {
			t_edge *edge = path[i];
			edge->flow += bottleNeck;
			minCost += bottleNeck * edge->cost;
		}
		maxFlow += bottleNeck;
		d_print_path(path);
		ft_printf("maxFlow: %d, minCost: %d\n", maxFlow, minCost);
		ft_printf("time: %d\n", compute_time(&g, maxFlow, minCost));
		path = bellman_ford(&g);
	}

	return 0;
}
