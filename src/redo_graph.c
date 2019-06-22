/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redo_graph.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalonso <nalonso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 16:46:49 by nalonso           #+#    #+#             */
/*   Updated: 2019/06/22 15:28:46 by nalonso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	delete_edge(t_graph *g, int src, int dst)
{
	t_node	*curr;
	size_t	j;

	curr = g->adj_list[src];
	j = 0;
	while (j < curr->nb_links)
	{
		if (curr->links[j])
		{
			if (curr->links[j]->to == dst)
				curr->links[j] = NULL;
		}
		j += 1;
	}
	curr = g->adj_list[dst];
	j = 0;
	while (j < curr->nb_links)
	{
		if (curr->links[j])
		{
			if (curr->links[j]->to == src)
				curr->links[j] = NULL;
		}
		j += 1;
	}
}

void	divide_node(t_graph *g, t_graph *sp, int i)
{
	t_node	*v_in;
	t_node	*v_out;
	t_edge	*un;
	int		curr_index;

	v_in = create_node(g->adj_list[i]->name);
	v_in->prev_index = i;
	v_in->type |= 1;
	v_out = create_node(g->adj_list[i]->name);
	v_out->prev_index = i;
	v_out->type |= 2;
	curr_index = sp->adj_vert;
	un = gb_malloc(&g_gb, sizeof(t_edge));
	un->to = curr_index + 1;
	un->from = curr_index;
	un->flow = 0;
	un->capacity = 1;
	un->rev = NULL;
	v_in->links = gb_malloc(&g_gb, sizeof(t_edge *) * (g->adj_vert * 2));
	v_in->links[v_in->nb_links++] = un;
	v_in->links[v_in->nb_links] = NULL;
	g->adj_list[i]->in_node = sp->adj_vert;
	g->adj_list[i]->out_node = sp->adj_vert + 1;
	append_node(sp, v_in);
	append_node(sp, v_out);
}

void	generate_new_structure(t_graph *g, t_graph *sp)
{
	int		i;
	t_node	*s;

	i = 0;
	while (i < g->adj_vert)
	{
		if (i == g->source.index || i == g->sink.index)
		{
			if (i == g->source.index)
				sp->source.index = sp->adj_vert;
			else
				sp->sink.index = sp->adj_vert;
			g->adj_list[i]->in_node = sp->adj_vert;
			g->adj_list[i]->out_node = sp->adj_vert;
			s = create_node(g->adj_list[i]->name);
			s->prev_index = (i == g->source.index)\
						? g->source.index : g->sink.index;
			append_node(sp, s);
			i += 1;
			continue;
		}
		divide_node(g, sp, i);
		i += 1;
	}
}

void	generate_directional_edges(t_graph *g, t_graph *sp)
{
	int		i;
	size_t	j;

	i = -1;
	while (++i < g->adj_vert)
	{
		if (i == g->source.index || i == g->sink.index)
			continue;
		j = 0;
		while (j < g->adj_list[i]->nb_links)
		{
			if (g->adj_list[i]->links[j] != NULL)
			{
				spe_add_edge(sp, g->adj_list[i]->out_node,\
					g->adj_list[g->adj_list[i]->links[j]->to]->in_node);
				spe_add_edge(sp,\
					g->adj_list[g->adj_list[i]->links[j]->to]->out_node,\
					g->adj_list[i]->in_node);
				delete_edge(g, i, g->adj_list[i]->links[j]->to);
			}
			j += 1;
		}
	}
}

void	redo_graph(t_graph *g, t_graph *special)
{
	size_t	i;

	init_graph(special, g->adj_vert * 2 + 1);
	generate_new_structure(g, special);
	spe_start_links(special);
	i = 0;
	while (i < g->adj_list[g->source.index]->nb_links)
	{
		spe_add_edge(special, special->source.index, \
			g->adj_list[g->adj_list[g->source.index]->links[i]->to]->in_node);
		delete_edge(g, g->source.index,\
			g->adj_list[g->source.index]->links[i]->to);
		i += 1;
	}
	generate_directional_edges(g, special);
}
