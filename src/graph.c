/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalonso <nalonso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 15:07:33 by jallen            #+#    #+#             */
/*   Updated: 2019/05/22 15:28:01 by nalonso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int			get_index(t_node **adj_list, char *name)
{
	size_t	i;

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

static void	setup_edge(t_graph *g, t_edge *s)
{
	size_t	i;
	size_t	j;

	j = g->adj_list[s->from]->nb_links;
	i = 0;
	while (i < j)
	{
		if (g->adj_list[s->from]->links[i]->to == s->to)
			break ;
		i += 1;
	}
	if (i == j)
	{
		g->adj_list[s->from]->links[g->adj_list[s->from]->nb_links] = s;
		g->adj_list[s->from]->nb_links += 1;
	}
}

int			add_edge(t_graph *graph, int src, int dst)
{
	t_edge	*s;
	t_edge	*d;

	if (src == -1 || dst == -1)
		return (0);
	s = malloc(sizeof(t_edge));
	d = malloc(sizeof(t_edge));
	if (!s || !d)
	{
		ft_fprintf(2, "Error: Malloc couldn't allocate the necessary memory\n");
		exit(EXIT_FAILURE);
	}
	
	s->to = dst;
	s->from = src;
	d->to = src;
	d->from = dst;
	s->rev = d;
	d->rev = s;
	setup_edge(graph, s);
	setup_edge(graph, d);
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

t_node		*create_node(char *name)
{
	t_node	*new;

	new = malloc(sizeof(*new));
	if (new)
	{
		new->name = name;
		new->links = NULL;
		new->nb_links = 0;
		new->ant = 0;
	}
	else
	{
		ft_fprintf(2, "Error: Malloc couldn't allocate the necessary memory\n");
		exit(EXIT_FAILURE);
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

void		free_graph(t_graph *g)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (g->adj_list[i] != NULL)
	{
		if (g->adj_list[i]->name != NULL)
			free(g->adj_list[i]->name);
		if (g->adj_list[i]->links != NULL)
		{
			j = 0;
			while (j < g->adj_list[i]->nb_links)
			{
				free(g->adj_list[i]->links[j]);
				j += 1;
			}
			free(g->adj_list[i]->links);
		}
		free(g->adj_list[i]);
		i += 1;
	}
	free(g->adj_list);
	g->adj_list = NULL;
	g->adj_vert = 0;
	g->adj_size = 0;
}
