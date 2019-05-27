/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalonso <nalonso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 14:59:29 by jallen            #+#    #+#             */
/*   Updated: 2019/05/27 16:13:27 by nalonso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	d_print_path(t_edge **path, t_graph g)
{
	int		i;

	i = 0;
	ft_printf("%s --> ", g.adj_list[g.source.index]->name);
	while (path[i])
	{
		if (path[i + 1])
			ft_fprintf(2, "%s --> ", g.adj_list[path[i]->to]->name);
		else
			ft_fprintf(2, "%s", g.adj_list[path[i]->to]->name);
		i++;
	}
}

void	d_print_paths(t_paths *head, t_graph *g)
{
	t_paths *ptr;

	ptr = head;
	ft_putendl_fd("------------------------------------", 2);
	while (ptr != NULL)
	{
		ft_fprintf(2, "path: {g}");
		d_print_path(ptr->path, *g);
		ft_fprintf(2, "{R} {b} path_len: %d predicted_ants: %f {R}\n",\
			ptr->len, ptr->predicted_ants);
		ptr = ptr->next;
	}
}
