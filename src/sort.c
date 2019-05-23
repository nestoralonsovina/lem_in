/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalonso <nalonso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 15:28:44 by nalonso           #+#    #+#             */
/*   Updated: 2019/05/22 15:28:53 by nalonso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

static void		split_list(t_paths *source, t_paths **front, t_paths **back)
{
	t_paths	*fast;
	t_paths	*slow;

	slow = source;
	fast = source->next;
	while (fast)
	{
		fast = fast->next;
		if (fast)
		{
			slow = slow->next;
			fast = fast->next;
		}
	}
	*front = source;
	*back = slow->next;
	slow->next = NULL;
}

static t_paths	*sort_and_merge(t_paths *a, t_paths *b)
{
	t_paths *result;

	result = NULL;
	if (!a)
		return (b);
	else if (!b)
		return (a);
	if (a->len <= b->len)
	{
		result = a;
		result->next = sort_and_merge(a->next, b);
	}
	else
	{
		result = b;
		result->next = sort_and_merge(a, b->next);
	}
	return (result);
}

void			merge_sort(t_paths **head_ref)
{
	t_paths *head;
	t_paths *a;
	t_paths *b;

	head = *head_ref;
	if (head == NULL || head->next == NULL)
	{
		return ;
	}
	split_list(head, &a, &b);
	merge_sort(&a);
	merge_sort(&b);
	*head_ref = sort_and_merge(a, b);
}
