/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flow_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbally <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 15:46:33 by hbally            #+#    #+#             */
/*   Updated: 2019/03/19 15:47:34 by hbally           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_node				*hop_get(t_list *hop_list)
{
	if (hop_list)
		return (((t_hop*)(hop_list->content))->hop_to);
	return (NULL);
}

t_node				*hop_get_flow(t_list *hop_list, int flow)
{
	t_list			*elem;
	t_hop			*hop;

	elem = hop_list;
	while (elem)
	{
		hop = (t_hop*)(elem->content);
		if (hop->flow <= flow)
			return (hop->hop_to);
		elem = elem->next;
	}
	return (NULL);
}

t_gate_data			*get_data(t_list *data_list, int flow)
{
	t_list			*elem;
	t_gate_data		*data;

	elem = data_list;
	while (elem)
	{
		data = (t_gate_data*)(elem->content);
		if (data->flow == flow)
			return (data);
		elem = elem->next;
	}
	return (NULL);
}

uint8_t				update_level(t_list **level, t_list **frontier)
{
	*level = *frontier;
	*frontier = NULL;
	if (*level == NULL)
		return (0);
	return (1);
}
