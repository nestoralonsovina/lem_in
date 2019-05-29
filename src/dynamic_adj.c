/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamic_adj.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 14:40:15 by jallen            #+#    #+#             */
/*   Updated: 2019/05/29 11:51:36 by nalonso          ###   ########.fr       */
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
