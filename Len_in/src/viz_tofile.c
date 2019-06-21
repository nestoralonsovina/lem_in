/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viz_tofile.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbally <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 16:24:02 by hbally            #+#    #+#             */
/*   Updated: 2019/03/19 16:47:23 by hbally           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "lem_in.h"
#include "libft.h"

int					create_file(t_wrap *wrap, char *path)
{
	int				fd;

	fd = open(path, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if (fd == -1)
		return (0);
	if (wrap)
		wrap->out_fd = fd;
	return (1);
}

void				parse_table(t_wrap *wrap, t_graph *graph, t_list **nodes,
									void (*action)(t_wrap*, t_list*))
{
	int				i;
	int				table_size;

	if (nodes)
	{
		table_size = graph->table_size;
		i = 0;
		while (i < table_size)
		{
			action(wrap, nodes[i]);
			i++;
		}
	}
}

static uint8_t		find_reverse_edge(t_node *parent, t_node *child)
{
	t_list			*edge;

	edge = child->edges;
	while (edge)
	{
		if ((t_node*)(edge->content) == parent)
			return (1);
		edge = edge->next;
	}
	return (0);
}

void				delete_duplicate(t_wrap *wrap, t_list *list)
{
	t_node			*parent;
	t_node			*child;
	t_list			*edge;
	t_list			*swap;

	(void)wrap;
	while (list)
	{
		parent = (t_node*)(list->content);
		edge = parent->edges;
		while (edge)
		{
			child = (t_node*)(edge->content);
			if (find_reverse_edge(parent, child))
			{
				swap = edge->next;
				del_one(edge, &(parent->edges));
				edge = swap;
			}
			else
				edge = edge->next;
		}
		list = list->next;
	}
}

void				graph_to_file(t_wrap *wrap, t_graph *graph)
{
	ft_dprintf(wrap->out_fd, "var sourceCapacity = %d;\n\n",
								graph->source_capacity);
	parse_table(wrap, graph, graph->nodes, &delete_duplicate);
	ft_dprintf(wrap->out_fd, "var nodes_data = [\n");
	parse_table(wrap, graph, graph->nodes, &nodes_to_file);
	ft_dprintf(wrap->out_fd, "]\n\n");
	ft_dprintf(wrap->out_fd, "var links_data = [\n");
	parse_table(wrap, graph, graph->nodes, &edges_to_file);
	ft_dprintf(wrap->out_fd, "]");
}
