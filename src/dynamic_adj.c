#include "../includes/lem_in.h"

/*
** Function: init_graph
** --------------------
** initialize t_graph structure
**
** g: pointer to graph
** initial_size: initial size of the adj_list array
*/

void	init_graph(t_graph *g, size_t initial_size)
{
	g->adj_list = malloc(initial_size * sizeof(t_node *));
	g->adj_size = initial_size;
	g->adj_vert = 0;
}

/*
** Function: append_node
** ---------------------
** append a new node to the graph, if enough size is allocated
** the node is added normally, if not we reallocate prev_size * 2.
**
** g: pointer to graph
** new_node: new node to be appended
*/

void	append_node(t_graph *g, t_node *new_node)
{
	int	tmp;

	if (g->adj_vert + 1 == g->adj_size)
	{
		tmp = g->adj_size;
		g->adj_size = tmp * 2;
		g->adj_list = (t_node **)realloc_tab((void **)g->adj_list,\
				g->adj_size * sizeof(new_node), tmp);
	}
	g->adj_list[g->adj_vert++] = new_node;
	g->adj_list[g->adj_vert] = NULL;
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

t_node	*create_node(char *name, int x, int y)
{
	t_node	*new;

	new = malloc(sizeof(*new));
	if (new)
	{
		new->name = ft_strdup(name);
		new->pos.x = x;
		new->pos.y = y;
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
		free(g->adj_list[i]);
		i += 1;
	}
	free(g->adj_list);
	g->adj_list = NULL;
	g->adj_vert = 0;
	g->adj_size = 0;
}
