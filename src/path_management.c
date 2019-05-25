/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalonso <nalonso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 14:36:52 by nalonso           #+#    #+#             */
/*   Updated: 2019/05/25 15:11:20 by nalonso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

static int		delete_unused_paths(t_paths **head)
{
	t_paths	*curr;
	int		changed;
	int		cnt;

	changed = 0;
	curr = *head;
	while (curr)
	{
		if (curr->predicted_ants <= 0)
		{
			changed = 1;
			delete_node(head, cnt);
			curr = *head;
			cnt = 0;
		}
		cnt++;
		curr = curr->next;
	}
	return (changed);
}

static void		calculate_ants(t_paths *head, t_graph *g, int debug)
{
	t_paths	*curr;

	curr = head;
	while (curr)
	{
		curr->predicted_ants = compute_ants(head, curr, g);
		curr = curr->next;
	}
}

int				plen(t_edge **p)
{
	int	i;

	i = 0;
	while (p[i] != NULL)
	{
		i++;
	}
	return (i);
}

void			delete_node(t_paths **head_ref, int key)
{
	t_paths	*temp;
	t_paths	*prev;
	int		cnt;

	temp = *head_ref;
	cnt = 0;
	if (temp != NULL && cnt == key)
	{
		*head_ref = temp->next;
		free(temp);
		return ;
	}
	while (temp != NULL && cnt != key)
	{
		prev = temp;
		temp = temp->next;
		cnt++;
	}
	if (temp == NULL)
		return ;
	prev->next = temp->next;
	free(temp);
}

t_paths			*trim_paths(t_paths *head, t_env env, t_graph *g)
{
	merge_sort(&head);
	calculate_ants(head, g, env.debug);
	while (delete_unused_paths(&head) == 1)
	{
		if (env.debug)
			ft_fprintf(2, "Recalculating ants... \n");
		calculate_ants(head, g, env.debug);
	}
	return (head);
}
