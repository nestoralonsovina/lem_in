/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalonso <nalonso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 13:43:48 by jallen            #+#    #+#             */
/*   Updated: 2019/06/22 15:23:56 by nalonso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

t_paths	*new_path(t_edge **p, int bg)
{
	t_paths		*ptr;

	ptr = NULL;
	ptr = gb_malloc(&g_gb, sizeof(t_paths));
	if (ptr != NULL)
	{
		ptr->path = p;
		ptr->len = plen(p);
		ptr->ants = 0;
		ptr->move = 0;
		ptr->predicted_ants = 0.0;
		ptr->bg = bg;
		ptr->next = NULL;
	}
	else
	{
		ft_putendl_fd(ERROR_MALLOC, 2);
		exit(EXIT_FAILURE);
	}
	return (ptr);
}

void	start_links(t_graph *g)
{
	int		i;

	i = 0;
	while (i < g->adj_vert)
	{
		g->adj_list[i]->links = gb_malloc(&g_gb, sizeof(t_edge) * g->adj_vert);
		if (!g->adj_list[i]->links)
		{
			ft_putendl_fd(ERROR_MALLOC, 2);
			exit(EXIT_FAILURE);
		}
		i += 1;
	}
}

void	append_path(t_paths **head, t_paths *new_path)
{
	t_paths *ptr;

	if (new_path)
	{
		if (*head == NULL)
		{
			*head = new_path;
		}
		else
		{
			ptr = *head;
			while (ptr->next)
			{
				ptr = ptr->next;
			}
			ptr->next = new_path;
		}
	}
}

int		count_paths(t_paths *head)
{
	if (!head)
		return (0);
	return (1 + count_paths(head->next));
}
