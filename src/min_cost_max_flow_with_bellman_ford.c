#include "../includes/lem_in.h"
#include <limits.h>

static int	ft_min(int a, int b) {
	return (a > b ? b : a);
}

/*
 ** Use the Bellman-Ford algorithm (which work with negative edge weight) to
 ** find an augmenting path through the flow network
 */

t_edge		**get_augmenting_path(t_graph *g) {

	int source = g->source.index;
	int sink = g->sink.index;
	int nodes = g->adj_vert;

	int dist[nodes];
	t_edge **pred = malloc(sizeof(t_edge *) * nodes);

	for (int i = 0; i < nodes; i++) {
		pred[i] = NULL;
		dist[i] = INT_MAX;
	}

	dist[source] = 0;
	// for each vertex, relax all the edges in the graph, O(VE)
	for (int i = 1; i < nodes - 1; i++) {
		for (int j = 0; j < nodes; j++) {
			for (int cur = 0; cur < g->adj_list[j]->nb_links; cur++) {
				t_edge *e = g->adj_list[j]->links[j];
				if ((e->cap - e->flow) > 0 && dist[j] + e->cost < dist[e->to]) {
					dist[e->to] = dist[j] + e->cost;
					pred[e->to] = e;
				}

			}
		}
	}

	return pred;
}

int			min_cos_max_flow_with_bellman_ford(t_graph *g) {
	ft_printf("Executing Minimum Cost Maximum flow algorithm using Bellman-Ford for path searching...\n");

	int source = g->source.index;
	int sink = g->sink.index;
	int nodes = g->adj_vert;


	g->pred = get_augmenting_path(g);
	print_path(create_path(g));


	return (1);
}

