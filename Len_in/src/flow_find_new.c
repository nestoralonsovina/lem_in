/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flow_find_new.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbally <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 15:49:52 by hbally            #+#    #+#             */
/*   Updated: 2019/03/19 17:29:33 by hbally           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "lem_in.h"

/*
** Check for legal edge
** 1. if child has already been visited,
**    or if we're going to source or from sink -> reject
** 2. if we know we're on an existing path -> accept
** 3. if child has a hop that goes to parent
**         -> we're on an existing path -> accept
** 4. if parent has any hop and we're not at start,
**    going to a fresh child -> reject
** 5. accept
*/

uint8_t				legal_edge_exception(t_node *parent, t_node *child)
{
	if (child->type == START || parent->type == END)
		return (1);
	if (parent->type == START && child->type == END)
	{
		if (child->parent == NULL)
		{
			child->parent = parent;
			return (0);
		}
		else
			return (1);
	}
	return (0);
}

uint8_t				legal_edge(t_node *parent, t_node *child, int flow)
{
	t_list			*parent_hop;
	t_list			*child_hop;

	parent_hop = parent->hop_data;
	child_hop = child->hop_data;
	if (child->last_visited == flow || legal_edge_exception(parent, child))
		return (0);
	if (parent->residual == flow)
	{
		if (hop_get(child_hop) == parent)
			child->residual = flow;
		return (1);
	}
	if (hop_get(child_hop) == parent)
		return ((child->residual = flow) == flow);
	if (hop_get(parent_hop))
	{
		if (parent->type == START && !(hop_get(child_hop)))
			return (1);
		return (0);
	}
	return (1);
}

void				update_child(t_wrap *wrap, t_node *parent, t_node *child,
									int flow)
{
	if (child->type == END)
		add_start(wrap, (void*)parent, &(wrap->bfs_output));
	else
	{
		child->last_visited = flow;
		child->parent = parent;
	}
}

void				flow_find_new(t_wrap *wrap, int flow, t_node *source)
{
	t_bfs			bfs;
	t_list			*edge;
	t_node			*parent;
	t_node			*child;

	ft_bzero(&bfs, sizeof(t_bfs));
	wrap->bfs_state = &bfs;
	add_start(wrap, (void*)source, &(bfs.frontier));
	while (update_level(&(bfs.level), &(bfs.frontier)))
		while (bfs.level)
		{
			parent = (t_node*)(bfs.level->content);
			edge = parent->edges;
			while (edge)
			{
				child = (t_node*)(edge->content);
				if (legal_edge(parent, child, flow))
				{
					update_child(wrap, parent, child, flow);
					add_start(wrap, child, &(bfs.frontier));
				}
				edge = edge->next;
			}
			del_one(bfs.level, &(bfs.level));
		}
}
