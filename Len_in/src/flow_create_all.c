/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flow_create_all.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbally <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 15:48:12 by hbally            #+#    #+#             */
/*   Updated: 2019/03/19 17:15:29 by hbally           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void				build_path(t_wrap *wrap, t_graph *graph, t_node *start)
{
	t_node			*node;
	t_list			**output;

	if (start)
	{
		del_all(&(wrap->bfs_output));
		output = &(wrap->bfs_output);
		node = start;
		add_start(wrap, (void*)(graph->sink), output);
		while (node)
		{
			add_start(wrap, (void*)node, output);
			node = node->parent;
		}
	}
}

int					get_path_value(t_node *path_start)
{
	t_node			*node;
	int				value;

	value = 1;
	node = path_start;
	while (node && node->parent)
	{
		value += hop_get(node->hop_data) == node->parent ? -1 : 1;
		node = node->parent;
	}
	return (value);
}

void				choose_best_path(t_wrap *wrap, t_graph *graph,
										t_list *candidate)
{
	int				best_value;
	int				value;
	t_node			*node;
	t_node			*best_path;

	best_value = 0;
	best_path = NULL;
	while (candidate)
	{
		node = (t_node*)(candidate->content);
		value = get_path_value(node);
		if (best_value == 0 || value < best_value)
		{
			best_value = value;
			best_path = node;
		}
		candidate = candidate->next;
	}
	build_path(wrap, graph, best_path);
}

void				flow_find_wrapper(t_wrap *wrap, t_graph *graph)
{
	del_all(&(wrap->bfs_output));
	graph->source->last_visited = graph->flow_max;
	flow_find_new(wrap, graph->flow_max, graph->source);
	wrap->bfs_state = NULL;
	choose_best_path(wrap, graph, wrap->bfs_output);
}

void				flow_create_all(t_wrap *wrap, t_graph *graph)
{
	graph->flow_max = 1;
	flow_find_wrapper(wrap, graph);
	while (wrap->bfs_output)
	{
		flow_update_nodes(wrap, wrap->bfs_output, graph->flow_max);
		flow_update_gates(wrap, graph->source, graph->flow_max);
		flow_simulate(graph, graph->source, graph->flow_max);
		graph->flow_max++;
		flow_find_wrapper(wrap, graph);
	}
}
