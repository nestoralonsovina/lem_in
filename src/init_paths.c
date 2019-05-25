/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 21:35:23 by jallen            #+#    #+#             */
/*   Updated: 2019/05/25 21:44:17 by jallen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

/*
** Function: create_path
** It should receive a pred and dist,
** arrays and form a two dimensional array of t_path
*/

t_path	*new_path_node(t_node *r, int len, int ant)
{
	t_path *n;

	n = malloc(sizeof(*n));
	n->room = r;
	n->len = len;
	n->ant = ant;
	return (n);
}

t_path	**create_path(t_graph *g, t_edge **p)
{
	int		i;
	int		len;
	t_path	**path;

	len = plen(p) + 1;
	path = (t_path **)malloc(sizeof(t_path *) * (len + 1));
	path[0] = new_path_node(g->adj_list[g->source.index], len, g->nb_ant);
	i = 1;
	while (i < len)
	{
		path[i] = new_path_node(g->adj_list[p[i - 1]->to], len, 0);
		i += 1;
	}
	path[i] = NULL;
	return (path);
}

/*
** Function: create_index
** returns an array with the index you have to move ants from
*/

int		*create_index(t_path **path)
{
	int		*a;
	int		i;
	int		j;
	int		len;

	i = 0;
	len = path[0]->len;
	j = len - 2;
	a = malloc(sizeof(int) * (len + 1));
	while (j >= 0)
	{
		if (path[j]->room->ant != 0)
			a[i++] = j;
		j -= 1;
	}
	a[i] = -1;
	return (a);
}

void	init_path(t_paths *head, t_graph *g)
{
	t_paths *ptr;

	ptr = head;
	g->adj_list[g->source.index]->ant = g->nb_ant;
	while (ptr)
	{
		ptr->move = create_path(g, ptr->path);
		ptr = ptr->next;
	}
}
