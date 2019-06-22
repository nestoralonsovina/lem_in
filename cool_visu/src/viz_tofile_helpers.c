/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viz_tofile_helpers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbally <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 16:45:35 by hbally            #+#    #+#             */
/*   Updated: 2019/03/19 16:46:48 by hbally           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lem_in.h"

void				move_to_file(t_wrap *wrap, t_node *source, t_node *target,
									int flag)
{
	static int		counter;

	if (flag == TURN_START)
	{
		if (!counter)
			ft_dprintf(wrap->out_fd, "\nvar turns_data = [\n");
		ft_dprintf(wrap->out_fd, "\t[\n");
		counter++;
	}
	if (flag == TURN_END)
		ft_dprintf(wrap->out_fd, "\t],\n");
	if (flag == LAST_TURN_END)
		ft_dprintf(wrap->out_fd, "\t]\n]");
	if (source && target)
		ft_dprintf(wrap->out_fd,
					"\t\t{\"source\": \"%s\", "
					"\"target\": \"%s\", "
					"\"num\": %d},\n",
					source->name, target->name, flag);
}

void				nodes_to_file(t_wrap *wrap, t_list *start)
{
	t_list			*elem;
	t_node			*node;

	elem = start;
	while (elem)
	{
		node = (t_node*)(elem->content);
		ft_dprintf(wrap->out_fd, "\t{\"name\": \"%s\", \"type\": %d},\n",
						node->name, node->type);
		elem = elem->next;
	}
}

void				edges_to_file(t_wrap *wrap, t_list *start)
{
	t_list			*elem;
	t_node			*parent;
	t_list			*edge;

	elem = start;
	while (elem)
	{
		parent = (t_node*)(elem->content);
		edge = parent->edges;
		while (edge)
		{
			ft_dprintf(wrap->out_fd,
							"\t{\"source\": \"%s\", \"target\": \"%s\"},\n",
							parent->name, ((t_node*)(edge->content))->name);
			edge = edge->next;
		}
		elem = elem->next;
	}
}
