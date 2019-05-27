/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   superposition.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalonso <nalonso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 15:29:25 by nalonso           #+#    #+#             */
/*   Updated: 2019/05/27 16:13:12 by nalonso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

static int		paths_collide(t_paths *p1, t_paths *p2, t_graph *g)
{
	int i;
	int j;

	i = 0;
	while (i < p1->len - 1)
	{
		j = 0;
		while (j < p2->len - 1)
		{
			if (g->adj_list[p1->path[i]->to]\
					== g->adj_list[p2->path[j]->to])
			{
				return (1);
			}
			j += 1;
		}
		i += 1;
	}
	return (0);
}

static double	ants_in_collision(t_paths *curr, t_paths *head, t_graph *g)
{
	double	ants;

	ants = 0.0;
	while (head)
	{
		if (head != curr && paths_collide(curr, head, g))
		{
			ants += head->predicted_ants;
		}
		head = head->next;
	}
	return (ants);
}

static void		delete_childs(t_paths *curr, t_paths *head, t_graph *g)
{
	int		counter;
	t_paths	*tmp;

	tmp = head;
	counter = 0;
	while (tmp)
	{
		if (tmp != curr && paths_collide(curr, tmp, g))
		{
			delete_node(&head, counter);
		}
		tmp = tmp->next;
		counter += 1;
	}
}

t_paths			*delete_superposition(t_paths *head, t_graph *g)
{
	t_paths	*tmp;
	double	collide;
	int		counter;

	tmp = head;
	counter = 0;
	collide = 0.0;
	while (tmp)
	{
		collide = ants_in_collision(tmp, head, g);
		if (collide > 0)
		{
			if (collide >= tmp->predicted_ants)
				delete_node(&head, counter);
			else
				delete_childs(tmp, head, g);
			tmp = head;
			counter = 0;
		}
		counter += 1;
		tmp = tmp->next;
	}
	return (head);
}
