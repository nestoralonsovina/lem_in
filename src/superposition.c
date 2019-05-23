/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   superposition.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalonso <nalonso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 15:29:25 by nalonso           #+#    #+#             */
/*   Updated: 2019/05/22 15:30:26 by nalonso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

static int		paths_collide(t_paths *p1, t_paths *p2)
{
	int i;
	int j;

	i = 0;
	while (p1->path[i])
	{
		j = 0;
		while (p2->path[j])
		{
			if (p1->path[i] == p2->path[j])
				return (1);
			j += 1;
		}
		i += 1;
	}
	return (0);
}

static double	ants_in_collision(t_paths *curr, t_paths *head)
{
	double	ants;

	ants = 0.0;
	while (head)
	{
		if (head != curr && paths_collide(curr, head) != 0)
		{
			ants += head->predicted_ants;
		}
		head = head->next;
	}
	return (ants);
}

static void		delete_childs(t_paths *curr, t_paths *head)
{
	int		counter;
	t_paths	*tmp;

	tmp = head;
	counter = 0;
	while (tmp)
	{
		if (tmp != curr && paths_collide(curr, tmp))
		{
			delete_node(&head, counter);
		}
		tmp = tmp->next;
		counter += 1;
	}
}

t_paths			*delete_superposition(t_paths *head, t_env env, t_graph *g)
{
	t_paths	*tmp;
	double	collide;
	int		counter;

	tmp = head;
	counter = 0;
	collide = 0.0;
	while (tmp)
	{
		collide = ants_in_collision(tmp, head);
		if (collide > 0)
		{
			if (collide >= tmp->predicted_ants)
				delete_node(&head, counter);
			else
				delete_childs(tmp, head);
			tmp = head;
			counter = 0;
		}
		counter += 1;
		tmp = tmp->next;
	}
	return (head);
}
