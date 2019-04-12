#include "../includes/lem_in.h"
#include <limits.h>
#include <stdbool.h>

int		ft_min(int a, int b) {
	return (a > b ? b : a);
}

void	readjust_flow(t_graph *g) {
	//int source = g->source.index;
	int destination = g->sink.index;
	int nodes = g->adj_vert;


	// iterate over all the nodes
	for (int i = 0; i < nodes; i++) {
		t_node *n = g->adj_list[i];

		for (size_t j = 0; j < n->nb_links; j++) {
			t_edge *e = n->links[j];

			// asign the capacity of the edge equal to the number of 
			// edges that come out of the receiving node
			e->cap = g->adj_list[e->to]->nb_links;
			if (e->to == destination) {
				d_print_edge(e);
				continue;
			}
		}
	}
}

int		EK(t_env *env, t_graph *g) {
	// adjust the flow in the final graph
	//readjust_flow(g);

	int source = g->source.index;
	int destination = g->sink.index;
	int nodes = g->adj_vert;

	(void)env;
	int flow = 0;
	while (true) {
		// run a bfs to find the shortes source-destination path.
		// we use 'pred' to stote the edge taken to get to each vertex.
		t_queue q = create_queue(nodes); // create a queue

		// push the source to the queue
		q.push(&q, source);

		t_edge **pred = malloc(sizeof(t_edge *) * nodes);

		for (int i = 0; i < nodes; i++) {
			pred[i] = NULL;
		}


		while (q.size != 0) {
			int cur = q.pop(&q);

			for (size_t i = 0; i < g->adj_list[cur]->nb_links; i++) {
				t_edge *e = g->adj_list[cur]->links[i];
				if (pred[e->to] == NULL && e->to != source && e->cap > e->flow) {
					pred[e->to] = e;
					q.push(&q, e->to);
				}
			}
		}

		// if we found an augmenting path to the dst
		if (pred[destination] != 0) {
			g->pred = pred;
			print_path(create_path(g));
			// see how much flow we can send throw the path
			int df = INT_MAX;

			t_edge *th = pred[destination];
			while (th) {
				df = ft_min(df, th->cap - th->flow);
				th = pred[th->from];
			}

			// update edges by that amount
			for (t_edge *e = pred[destination]; e != NULL; e = pred[e->from]) {
				e->flow = e->flow + df;
			}
			flow += df;
		} else {
			// no path was found so we stop the loop
			break ;
		}
	}
	return flow;
}
