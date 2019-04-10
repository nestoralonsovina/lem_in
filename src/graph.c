#include "../includes/lem_in.h"

/*
** Function: get_index
** ---------------------
** returns the index of the wanted node if it does exit
**
** adj_list: array of vertex
** name: name of the node to search
**
** return: index -> successfull -1 -> failure
*/

int		get_index(t_node **adj_list, char *name)
{
	size_t i;

	i = 0;
	while (adj_list[i] != NULL)
	{
		if (ft_strequ(adj_list[i]->name, name))
			return (i);
		i += 1;
	}
	return (-1);
}

/*
** Function: add_edge
** ---------------------
** adds an edge to graph from src to dst
**
** graph: graph where the link is added
** src: index of the src vertex
** dst: index of the dst vertex
**
** return: pointer to the newly created node
*/

int			add_edge(t_graph *graph, int src, int dst)
{
	t_edge	s;
	t_edge	d;

	if (src == -1 || dst == -1)
		return (0);
	s.to = dst;
	s.from = src;
	s.flow = 0;
	s.cap = 0;

	d.to = src;
	d.from = dst;
	d.flow = 0;
	d.cap = 0;

	size_t i = 0;
	size_t j = graph->adj_list[src]->nb_links;

	while (i < j) {
		if (graph->adj_list[src]->links[i].to == s.to) {
			break ;
		}
		i += 1;
	}
	if (i == j) {
		graph->adj_list[src]->links[graph->adj_list[src]->nb_links] = s;
		graph->adj_list[src]->nb_links += 1;
	}

	i = 0;
	j = graph->adj_list[dst]->nb_links;

	while (i < j) {
		if (graph->adj_list[dst]->links[i].to == d.to) {
			break ;
		}
		i += 1;
	}
	if (i == j) {
		graph->adj_list[dst]->links[graph->adj_list[dst]->nb_links] = d;
		graph->adj_list[dst]->nb_links += 1;
	}

	return (1);
}

/*
** Function: create_node
** ---------------------
** creates new instance of t_node and returns it, initializing
** name and pos.
**
** name: name of the room/node
** x,y: 2D positions of the node
**
** return: pointer to the newly created node
*/

t_node	*create_node(char *name)
{
	t_node	*new;

	new = malloc(sizeof(*new));
	if (new)
	{
		new->name = name;
		new->links = NULL;
		new->nb_links = 0;
	}
	return (new);
}

/*
** Function: free_graph
** ---------------------
** free's the allocated memory in adj_list and resets it's parameters
**
** g: pointer to graph
*/

void	free_graph(t_graph *g)
{
	size_t	i;

	i = 0;
	while (g->adj_list[i] != NULL)
	{
		if (g->adj_list[i]->name != NULL)
			free(g->adj_list[i]->name);
		if (g->adj_list[i]->links != NULL)
			free(g->adj_list[i]->links);
		free(g->adj_list[i]);
		i += 1;
	}
	free(g->adj_list);
	g->adj_list = NULL;
	g->adj_vert = 0;
	g->adj_size = 0;
}
