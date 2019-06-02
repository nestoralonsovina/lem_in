/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalonso <nalonso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 13:43:48 by jallen            #+#    #+#             */
/*   Updated: 2019/06/01 17:27:18 by jallen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

t_paths	*new_path(t_edge **p, int bg)
{
	t_paths		*ptr;

	ptr = NULL;
	ptr = (t_paths *)malloc(sizeof(t_paths));
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
		g->adj_list[i]->links = malloc(sizeof(t_edge) * g->adj_vert);
		if (!g->adj_list[i]->links)
		{
			ft_putendl_fd(ERROR_MALLOC, 2);
			exit(EXIT_FAILURE);
		}
		i += 1;
	}
}

int		print_error(void)
{
	ft_fprintf(2, "ERROR\n");
	return (0);
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
