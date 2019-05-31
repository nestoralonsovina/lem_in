/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalonso <nalonso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 14:59:29 by jallen            #+#    #+#             */
/*   Updated: 2019/05/31 16:37:33 by jallen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	info_paths(t_paths *head, t_graph *g, int cnt, int debug)
{
	int	len;

	len = count_paths(head);
	if (debug & D)
		d_print_paths(head, g);
	if (debug & I)
	{
		ft_putendl_fd("", 2);
		ft_fprintf(2, "{y}Ants at start :{R}                 %i\n", g->nb_ant);
		ft_fprintf(2, "{y}Paths at start :{R}                %i\n",\
				g->nb_p);
		ft_fprintf(2, "{y}Chosen Paths :{R}                  %i\n",\
				len);
		ft_fprintf(2, "{y}Total number of lines printed :{R} %i\n",
				cnt);
	}
}

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
	ft_putendl_fd("\n------------------------------------", 2);
	while (ptr != NULL)
	{
		ft_fprintf(2, "path: {g}");
		d_print_path(ptr->path, *g);
		ft_fprintf(2, "{R} {b} path_len: %d predicted_ants: %i {R}\n",\
				ptr->len, ptr->ants);
		ptr = ptr->next;
	}
	ft_putendl_fd("------------------------------------", 2);
}
