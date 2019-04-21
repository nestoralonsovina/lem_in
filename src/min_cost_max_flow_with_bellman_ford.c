#include "../includes/lem_in.h"
#include <limits.h>

#define DEBUG_LEVEL 1
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

static int remaining_capacity(t_edge *e) {
	return e->cap - e->flow;
}

static void f_secure(void **p) {
	if (p) {
		free(p);
	}
}

static void d_print_path(t_edge **path, t_graph *g) {
	int i = 0;


	ft_printf("%s --> ", g->adj_list[g->source.index]->name);
	while (path[i]) {
		if (path[i + 1])
			ft_printf("%s --> ", g->adj_list[path[i]->to]->name);
		else
			ft_printf("%s\n", g->adj_list[path[i]->to]->name);
		i++;
	}
}

static void p_edge_pair(t_edge *edge) {
	ft_printf("{g}%d->%d - %d/%d@%d{R}", edge->to, edge->from, edge->flow, edge->cap, edge->cost); 
	ft_printf("\t{r}%d->%d - %d/%d@%d\n{R}", edge->rev->to, edge->rev->from, edge->rev->flow, edge->rev->cap, edge->rev->cost); 
}

/*
 ** Use the Bellman-Ford algorithm (which work with negative edge weight) to
 ** find an augmenting path through the flow network
 */

t_edge		**bellman_ford(t_env env, t_graph *g) {
	int n = g->adj_vert;
	int s = g->source.index;
	int d = g->sink.index;

	int dist[n];
	t_edge **prev = malloc(sizeof(t_edge *) * (n + 1));

	for (int i = 0; i < n; i++) {
		dist[i] = INT_MAX;
		prev[i] = NULL; 
	}

	dist[s] = 0;
	for (int i = 0; i < n - 1; i++) { //relax all the edges repeatedly
		for (int j = 0; j < n; j++) { // iterate through the vertices
			if (env.debug && DEBUG_LEVEL == 2) {
				ft_printf("vertice %d, room: %s:\n", j, g->adj_list[j]->name);
			}
			for (int e = 0; e < g->adj_list[j]->nb_links; e++) { // iterate through the edges of each vertice
				t_edge *edge = g->adj_list[j]->links[e];

				if (env.debug && DEBUG_LEVEL == 2) {
					ft_printf("\t->%d - %d/%d@%d\n", edge->to, edge->flow, edge->cap, edge->cost); 
				}

				if (edge != NULL \
						&& dist[edge->from] != INT_MAX \
						&& dist[edge->from] + edge->cost < dist[edge->to]\
						&& remaining_capacity(edge) > 0) {
					dist[edge->to] = dist[edge->from] + edge->cost;
					prev[edge->to] = edge;
				}

				if (edge != NULL) {
					if (dist[edge->from] != INT_MAX \
							&& dist[edge->from] + edge->cost < dist[edge->to]\
							&& (edge->cap - edge->flow) > 0) {

					}

				}
			}
		}
	}
	p_array(dist,n);
	if (!prev[d])
		return NULL;

	int l = dist[d];
	t_edge **path = malloc(sizeof(t_edge *) * (l + 1));
	path[l--] = NULL;
	for (t_edge *e = prev[d]; e != NULL; e = prev[e->from]) {
		path[l--] = e;
	}
	return path;
}

int			min_cost_max_flow_with_bellman_ford(t_env env, t_graph g) {

	t_paths *head;
	t_edge **path;
	int minCost = 0;
	int maxFlow = 0;

	path = bellman_ford(env, &g);
	head = NULL;
	while (path != NULL)
	{
		int bottleNeck = INT_MAX;
		for (int i = 0; i < len(path); i++) {
			t_edge *edge = path[i];
			bottleNeck = ft_min(bottleNeck, edge->cap - edge->flow);
		}

		for (int i =0; i < len(path); i++) {
			t_edge *edge = path[i];
			edge->flow += bottleNeck;
			edge->rev->flow -= bottleNeck;
			minCost += bottleNeck * edge->cost;
		}
		//
		for (int i =0; i < len(path); i++) {
			t_edge *edge = path[i];
			p_edge_pair(edge);
		}
		//
		maxFlow += bottleNeck;
		if (env.debug) {
			ft_printf("maxFlow: %d, minCost: %d\n", maxFlow, minCost);
			d_print_path(path, &g);
		}

		if (head != NULL)
		{
			for (int i = 0; i < len(path); i++) {
				intersects(head, path[i]);
			}
		}

		t_paths *p = new_path(path, maxFlow, minCost, g.nb_ant);
		head = append_path(head, p);
		path = bellman_ford(env, &g);
		if (env.debug) {
			for (int j = 0; j < g.adj_vert; j++) {
				ft_printf("vertice %d, room: %s:\n", j, g.adj_list[j]->name);
				for (int e = 0; e < g.adj_list[e]->nb_links; e++) {
					t_edge *edge = g.adj_list[j]->links[e];
					ft_printf("\t->%d - %d/%d@%d\n", edge->to, edge->flow, edge->cap, edge->cost); 
				}
			}
		}
	}
	if (env.debug && path == NULL) {
		ft_fprintf(2, "No more paths found, number of paths: %d\n", maxFlow);
	}


	return 0;
}
