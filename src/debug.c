/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 14:59:29 by jallen            #+#    #+#             */
/*   Updated: 2019/05/14 15:04:10 by jallen           ###   ########.fr       */
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
			ft_printf("%s --> ", g.adj_list[path[i]->to]->name);
		else
			ft_printf("%s", g.adj_list[path[i]->to]->name);
		i++;
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
