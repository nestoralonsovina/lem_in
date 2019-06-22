/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalonso <nalonso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 21:20:24 by jallen            #+#    #+#             */
/*   Updated: 2019/06/22 15:22:46 by nalonso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

double		calculate_ants(t_paths *head, t_graph *g)
{
	t_paths *curr;
	double	last_prediction;

	curr = head;
	g->predicted = 0;
	while (curr)
	{
		curr->predicted_ants = compute_ants(head, curr, g);
		curr->ants = curr->predicted_ants;
		g->predicted += curr->predicted_ants;
		if (!curr->next)
		{
			last_prediction = curr->predicted_ants;
		}
		curr = curr->next;
	}
	return (last_prediction);
}

static void	adding_extra(t_paths *head, t_graph *g)
{
	t_paths *ptr;

	ptr = head;
	while (g->predicted < g->nb_ant)
	{
		if (ptr->next == NULL)
			ptr = head;
		ptr->predicted_ants += 1;
		ptr = ptr->next;
		g->predicted++;
	}
}

t_paths		*trim_paths(t_paths *head, t_graph *g)
{
	merge_sort(&head);
	calculate_ants(head, g);
	if (g->nb_ant != g->predicted)
		adding_extra(head, g);
	return (head);
}
