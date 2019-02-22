#include "../includes/lem_in.h"

t_graph		*create_graph(int vertices)
{
	t_graph	*graph;
	int		i;

	i = 0;
	graph = (t_graph *)malloc(sizeof(t_graph));
	graph->num_vertices = vertices;
	graph->adj_list = (t_node **)malloc(vertices * sizeof(t_node *));
	while (i < vertices)
		graph->adj_list[i] = NULL;
	return (graph);
}

t_node		*create_node(int v)
{
	t_node	*new_node;

	new_node = (t_node *)malloc(sizeof(t_node));
	new_node->vertex = v;
	new_node->next = NULL;
	return (new_node);
}

void		add_edge(t_graph *graph, int src, int dest)
{
	t_node *new_node;

	// add edge from src to dest
	new_node = create_node(dest);
	new_node->next = graph->adj_list[src];
	graph->adj_list[src] = new_node;

	// add edge from dest to src
	new_node = create_node(src);
	new_node->next = graph->adj_list[dest];
	graph->adj_list[dest] = new_node;
}

void		print_graph(t_graph *graph, char **rooms)
{
	int		v;
	t_node	*tmp;

	v = 0;
	while (v < graph->num_vertices)
	{
		tmp = graph->adj_list[v];
		ft_printf("\n Adjacency list of vertex %d\n ", v);
		while (tmp)
		{
			ft_printf("%s -> ", rooms[tmp->vertex]);
			tmp = tmp->next;
		}
		ft_putendl(0);
		v += 1;
	}
}
