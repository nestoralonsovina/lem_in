/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flow_simulate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbally <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 16:06:50 by hbally            #+#    #+#             */
/*   Updated: 2019/03/20 12:04:07 by hbally           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lem_in.h"

int					get_cost(t_gate_data *data)
{
	if (data && data->crowding != 0)
		return (data->path_len + data->crowding - 1);
	return (0);
}

t_node				*get_best_gate(t_node *source, int flow)
{
	void			*best_gate;
	int				best_len;
	t_list			*edge;
	t_gate_data		*data;

	edge = source->edges;
	best_len = -1;
	while (edge)
	{
		data = get_data(((t_node*)(edge->content))->gate_data, flow);
		if (data && (best_len < 0
				|| data->path_len + data->crowding < best_len))
		{
			best_gate = edge->content;
			best_len = data->path_len + data->crowding;
		}
		edge = edge->next;
	}
	return ((t_node*)best_gate);
}

void				delete_duplicate_edges(t_node *source)
{
	t_list			*current;
	t_list			*parse;
	t_list			*swap;

	current = source->edges;
	while (current)
	{
		parse = source->edges;
		while (parse)
		{
			if (parse != current
					&& (t_node*)(parse->content) == (t_node*)(current->content))
			{
				swap = parse->next;
				del_one(parse, &(source->edges));
				parse = swap;
			}
			else
				parse = parse->next;
		}
		current = current->next;
	}
}

void				flow_simulate(t_graph *graph, t_node *source, int flow)
{
	int				remaining;
	int				cost;
	int				max_cost;
	t_list			*edge;

	if (flow == 1)
		delete_duplicate_edges(source);
	remaining = graph->source_capacity;
	while (remaining--)
		get_data(get_best_gate(source, flow)->gate_data, flow)->crowding += 1;
	max_cost = 0;
	edge = source->edges;
	while (edge)
	{
		cost = get_cost(get_data(((t_node*)(edge->content))->gate_data, flow));
		if (cost && (!max_cost || cost > max_cost))
			max_cost = cost;
		edge = edge->next;
	}
	if (!graph->flow_best_cost || max_cost < graph->flow_best_cost)
	{
		graph->flow_best = flow;
		graph->flow_best_cost = max_cost;
	}
}
