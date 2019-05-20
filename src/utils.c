/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalonso <nalonso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 13:43:48 by jallen            #+#    #+#             */
/*   Updated: 2019/05/20 11:00:34 by nalonso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int plen(t_edge **p)
{
	int i;

	i = 0;
	while (p[i] != NULL)
	{
		i++;
	}
	return (i);
}

static int	compute_time(int ants, int mf, int mc)
{
	return ((ants / mf) + mc);
}

t_paths		*new_path(t_edge **p, int max_flow, int min_cost, int nb_ant, int parent)
{
	t_paths		*ptr;

	ptr = (t_paths *)malloc(sizeof(t_paths));
	if (ptr != NULL)
	{
		ptr->path = p;
		ptr->mf = max_flow;
		ptr->mc = min_cost;
		ptr->time = compute_time(nb_ant, max_flow, min_cost);
		ptr->next = NULL;
		ptr->len = plen(p);
		ptr->parent = parent;
	}
	return (ptr);
}

void		append_path(t_paths **head, t_paths *new_path)
{
	t_paths *ptr;

	if (new_path)
	{
		if (*head == NULL)
		{
			new_path->id = 1;
			*head = new_path;
		}
		else
		{
			ptr = *head;
			while (ptr->next)
			{
				ptr = ptr->next;
			}
			new_path->id = ptr->id + 1;
			ptr->next = new_path;
		}
	}
}

int			count_paths(t_paths *head)
{
	if (!head)
		return (0);
	return (1 + count_paths(head->next));
}
