/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gb_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 09:18:24 by jallen            #+#    #+#             */
/*   Updated: 2019/06/04 11:33:48 by jallen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/gb_collector.h"

t_lst	*g_new()
{
	t_lst	*n;

	n = NULL;
	if (!(n = malloc(sizeof(t_lst))))
		return (NULL);
	n->content = NULL;
	n->size = 0;
	n->arr = NULL;
	n->next = NULL;
	return (n);
}

void	g_add(t_lst **head, t_lst *new)
{
	new->next = *head;
	*head = new;
}

void	*gb_malloc(void	*content, size_t size)
{
	lst_add(&head, new());
	if (!(head->content = (void *)malloc(sizeof(void) * size)))
		return (0);
	head->size = size;
	return (head->content);	
}
