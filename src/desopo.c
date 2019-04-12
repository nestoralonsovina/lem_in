#include "../includes/lem_in.h"

#include <limits.h>

void shortest_paths(t_graph *g, int *dist, t_edge **pred) {
	int source = g->source.index;
	int sink = g->sink.index;
	int nodes = g->adj_vert;


	int visited[nodes];
	for (int i = 0; i < nodes; i++) {
		pred[i] = NULL;
		dist[i] = INT_MAX;
		visited[i] = 2;
	}

	t_queue q = create_queue(nodes);

	q.push(&q, source);
	dist[source] = 0;


	while (q.size != 0) {
		int cur = q.pop();
	}

}
