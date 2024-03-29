/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_ants.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 21:29:20 by jallen            #+#    #+#             */
/*   Updated: 2019/05/27 16:05:52 by nalonso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

static int	sum_lengths(t_paths *l)
{
	if (!l)
		return (0);
	return (l->len + sum_lengths(l->next));
}

int			plen(t_edge **p)
{
	int	i;

	i = 0;
	while (p[i] != NULL)
		i++;
	return (i);
}

double		compute_ants(t_paths *head, t_paths *cur, t_graph *g)
{
	int	nb_paths;

	nb_paths = count_paths(head);
	return ((g->nb_ant - ((nb_paths - 1) * (cur->len)\
					- (sum_lengths(head) - (cur->len)))) / nb_paths);
}
