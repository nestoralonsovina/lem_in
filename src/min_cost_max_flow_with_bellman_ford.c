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

static void f_secure(void **p) {
    if (p) {
        free(p);
    }
}

static int compute_time(t_graph *g, int mf, int mc) {
    return ((g->nb_ant / mf) + mc);
}

static void d_print_path(t_edge **path, t_graph *g) {
    int i = 0;

    while (path[i]) {
        if (path[i + 1])
            ft_printf("%s --> ", g->adj_list[path[i]->to]->name);
        else
            ft_printf("%s\n", g->adj_list[path[i]->to]->name);
        i++;
    }
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
                ft_printf("vertice %d:\n", j);
            }
            for (int e = 0; e < g->adj_list[j]->nb_links; e++) { // iterate through the edges of each vertice
                t_edge *edge = g->adj_list[j]->links[e];

                if (env.debug && DEBUG_LEVEL == 2) {
                    ft_printf("\t->%d - %d/%d@%d\n", edge->to, edge->flow, edge->cap, edge->cost); 
                }
                if (edge != NULL \
                        && dist[edge->from] != INT_MAX \
                        && dist[edge->from] + edge->cost < dist[edge->to]\
                        && (edge->cap - edge->flow) > 0) {
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

    if (!prev[d])
        return NULL;

    //p_array(dist, n);
    int l = dist[d];
    t_edge **path = malloc(sizeof(t_edge *) * (l + 1));
    path[l--] = NULL;
    for (t_edge *e = prev[d]; e != NULL; e = prev[e->from]) {
        path[l--] = e;
    }
    f_secure(prev);
    return path;
}

int			min_cost_max_flow_with_bellman_ford(t_env env, t_graph g) {

    /***  changes to the flow & capaticty  ***/

    t_node *n_source = create_node("s_out");
    int s_index = g.adj_vert;
    append_node(&g, n_source);

    g.adj_list[s_index]->links = g.adj_list[g.source.index]->links;
    g.adj_list[s_index]->nb_links = g.adj_list[g.source.index]->nb_links;

    g.adj_list[g.source.index]->links = malloc(sizeof(t_edge *) * g.adj_vert);
    g.adj_list[g.source.index]->nb_links = 0;

    add_edge(&g, g.source.index, s_index, g.nb_ant);

    t_node *n_sink = create_node("d_out"); 
    int d_index = g.adj_vert;
    append_node(&g, n_sink);

    g.adj_list[d_index]->links = g.adj_list[g.sink.index]->links;
    g.adj_list[d_index]->nb_links = g.adj_list[g.sink.index]->nb_links;

    g.adj_list[g.sink.index]->links = malloc(sizeof(t_edge *) * g.adj_vert);
    g.adj_list[g.sink.index]->nb_links = 0;

    add_edge(&g, g.sink.index, d_index, g.nb_ant * -1);



     /***  end of modifications  ***/


    t_edge **path;
    int minCost = 0;
    int maxFlow = 0;

    path = bellman_ford(env, &g);
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
        if (env.debug) {
            ft_printf("maxFlow: %d, minCost: %d\n", maxFlow, minCost);
            ft_printf("time: %d\n", compute_time(&g, maxFlow, minCost));
            d_print_path(path, &g);
        }
        f_secure(path);
        path = bellman_ford(env, &g);
    }
    if (env.debug && path == NULL) {
        ft_fprintf(2, "No more paths found, number of paths: %d\n", maxFlow);
    }


    return 0;
}
