/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_ants.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalonso <nalonso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 15:11:38 by nalonso           #+#    #+#             */
/*   Updated: 2019/05/25 17:43:12 by nalonso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	sum_lengths(t_paths *head)
{
	if (!head)
		return (0);
	return (head->len + sum_lengths(head->next));
}

double		compute_ants(t_paths *head, t_paths *cur, t_graph *g)
{
	int nb_paths;
	int	len_paths;

	nb_paths = count_paths(head);
	len_paths = sum_lengths(head) - cur->len;
	return (g->nb_ant - ((nb_paths - 1) * cur->len - (len_paths)) / nb_paths);
}
