/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbally <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 16:10:50 by hbally            #+#    #+#             */
/*   Updated: 2019/03/19 16:11:21 by hbally           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "lem_in.h"
#include "libft.h"

void				ft_free_node(t_node *node)
{
	t_list			*gate_data;

	if (node->edges)
		del_all(&(node->edges));
	if (node->name)
		ft_memdel((void**)&(node->name));
	ft_free_hop(node);
	if (node->gate_data)
	{
		gate_data = node->gate_data;
		while (gate_data)
		{
			if (gate_data->content)
				ft_memdel((void**)&(gate_data->content));
			gate_data = gate_data->next;
		}
		del_all(&(node->gate_data));
	}
	ft_memdel((void**)&node);
}

void				ft_free_nodes_list(t_list *lst)
{
	t_list *tmp;

	while (lst)
	{
		tmp = lst->next;
		if (lst->content)
			ft_free_node((t_node*)lst->content);
		ft_memdel((void**)&lst);
		lst = tmp;
	}
}

void				ft_free_graph(t_graph *graph)
{
	t_list	**tab;
	int		size;
	int		i;

	if (graph->nodes)
	{
		tab = graph->nodes;
		size = graph->table_size;
		i = 0;
		while (i < size)
		{
			if (tab[i])
				ft_free_nodes_list(tab[i]);
			i++;
		}
		free(graph->nodes);
		graph->nodes = NULL;
	}
}

void				ft_free_list(t_list *lst)
{
	t_list *tmp;

	while (lst)
	{
		tmp = lst->next;
		if (lst->content != NULL)
			ft_memdel((void**)&(lst->content));
		ft_memdel((void**)&(lst));
		lst = tmp;
	}
}

void				ft_free_wrap(t_wrap *wrap)
{
	ft_free_list(wrap->input_start);
	wrap->input_end = NULL;
	ft_free_graph(&(wrap->graph));
	if (wrap->bfs_state)
	{
		if (wrap->bfs_state->level)
			del_all(&(wrap->bfs_state->level));
		if (wrap->bfs_state->frontier)
			del_all(&(wrap->bfs_state->frontier));
		wrap->bfs_state->frontier_end = NULL;
	}
	if (wrap->bfs_output)
		del_all(&(wrap->bfs_output));
}
