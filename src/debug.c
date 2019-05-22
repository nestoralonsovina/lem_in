/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalonso <nalonso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 14:59:29 by jallen            #+#    #+#             */
/*   Updated: 2019/05/22 14:20:31 by nalonso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	d_print_edge(t_edge *e)
{
	ft_printf("to: %d, from: %d,", e->to, e->from);
	ft_printf(" flow: %d, cap: %d\n", e->flow, e->cap);
}

void	d_print_links(t_graph *g)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (g->adj_list[i] != NULL)
	{
		ft_printf("%s - links: %d\n", g->adj_list[i]->name,
				g->adj_list[i]->nb_links);
		while (j < g->adj_list[i]->nb_links)
		{
			ft_printf("{g}%5s{R} %s\n", "-->",\
					g->adj_list[g->adj_list[i]->links[j]->to]->name);
			j += 1;
		}
		j = 0;
		i += 1;
		ft_printf("\n");
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

void d_print_paths(t_paths *head, t_graph *g)
{
	ft_putendl_fd("------------------------------------", 2);
	t_paths *ptr = head;
	while (ptr != NULL)
	{
		if (ptr->parent)
			ft_fprintf(2, "path: {r}");
		else
			ft_fprintf(2, "path: {g}");
		d_print_path(ptr->path, *g);
		ft_fprintf(2, "{R} {b} plen: %d cost: %d | flow: %d{R} {y} time: %d id: %d{R}\n", ptr->len, ptr->mc, ptr->mf, ptr->time, ptr->id);
		ptr = ptr->next;
	}
}
void	start_links(t_graph *g)
{
	int		i;

	i = 0;
	while (i < g->adj_vert)
	{
		g->adj_list[i]->links = malloc(sizeof(t_edge) * g->adj_vert);
		i += 1;
	}
}

int		print_error(void)
{
	ft_fprintf(2, "ERROR\n");
	return (0);
}
