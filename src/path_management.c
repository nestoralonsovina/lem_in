/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalonso <nalonso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 21:20:24 by jallen            #+#    #+#             */
/*   Updated: 2019/05/31 16:38:56 by jallen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void		delete_node(t_paths **head_ref, int key)
{
	t_paths	*temp;
	t_paths	*prev;
	int		cnt;

	cnt = 0;
	temp = *head_ref;
	if (temp != NULL && cnt == key)
	{
		*head_ref = temp->next;
		free(temp->path);
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

static int	delete_unused_paths(t_paths **head)
{
	t_paths	*curr;
	int		changed;
	int		cnt;

	cnt = 0;
	changed = 0;
	curr = *head;
	while (curr)
	{
		if (curr->predicted_ants < 1)
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
	while (delete_unused_paths(&head) == 1)
	{
		calculate_ants(head, g);
	}
	if (g->nb_ant != g->predicted)
		adding_extra(head, g);
	return (head);
}
