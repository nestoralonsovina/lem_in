/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flow_update.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbally <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 16:08:52 by hbally            #+#    #+#             */
/*   Updated: 2019/03/19 17:29:33 by hbally           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lem_in.h"

int					get_path_len(t_node *start)
{
	t_node			*node;
	int				hop_count;

	node = start;
	hop_count = 1;
	while (node->hop_data)
	{
		node = ((t_hop*)(node->hop_data->content))->hop_to;
		hop_count++;
	}
	return (hop_count);
}

void				flow_update_gates(t_wrap *wrap, t_node *source, int flow)
{
	t_list			*hop;
	t_node			*gate;
	t_gate_data		*data;

	hop = source->hop_data;
	while (hop)
	{
		gate = ((t_hop*)(hop->content))->hop_to;
		data = (t_gate_data*)ft_memalloc(sizeof(t_gate_data));
		data->flow = flow;
		data->path_len = get_path_len(gate);
		add_start(wrap, (void*)data, &(gate->gate_data));
		hop = hop->next;
	}
}

void				flow_update_nodes(t_wrap *wrap, t_list *path, int flow)
{
	t_node			*node;
	t_node			*next_node;
	t_hop			*hop;

	while (path->next)
	{
		node = (t_node*)(path->content);
		next_node = (t_node*)(path->next->content);
		hop = (t_hop*)ft_memalloc(sizeof(t_hop));
		hop->flow = flow;
		if (next_node->hop_data
				&& ((t_hop*)(next_node->hop_data->content))->hop_to == node)
		{
			hop->hop_to = NULL;
			add_start(wrap, (void*)hop, &(next_node->hop_data));
		}
		else
		{
			hop->hop_to = next_node;
			add_start(wrap, (void*)hop, &(node->hop_data));
		}
		path = path->next;
	}
}
