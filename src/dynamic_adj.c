/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamic_adj.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalonso <nalonso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 14:40:15 by jallen            #+#    #+#             */
/*   Updated: 2019/06/22 15:28:44 by nalonso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (!g->adj_list)
	{
		ft_putendl_fd(ERROR_MALLOC, 2);
		exit(EXIT_FAILURE);
	}
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

t_edge	*spe_add_edge(t_graph *g, int src, int dst)
{
	t_edge	*e;

	e = gb_malloc(&g_gb, sizeof(t_edge));
	e->flow = 0;
	e->from = src;
	e->to = dst;
	e->capacity = 2147483647;
	e->rev = NULL;
	g->adj_list[src]->links[g->adj_list[src]->nb_links++] = e;
	g->adj_list[src]->links[g->adj_list[src]->nb_links] = NULL;
	return (e);
}

void	spe_start_links(t_graph *sp)
{
	int	i;
	int	z;

	i = 0;
	while (i < sp->adj_vert)
	{
		if ((sp->adj_list[i]->type & 1) == 0)
		{
			sp->adj_list[i]->links =\
				gb_malloc(&g_gb, sizeof(t_edge *) * sp->adj_vert + 1);
			z = 0;
			while (z < sp->adj_vert)
				sp->adj_list[i]->links[z++] = NULL;
		}
		++i;
	}
}
