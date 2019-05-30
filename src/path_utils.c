/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalonso <nalonso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 12:26:51 by nalonso           #+#    #+#             */
/*   Updated: 2019/05/29 15:14:12 by jallen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	unvisit_path(t_edge **path, t_edge *intersection)
{
	int i;

	i = 0;
	while (path[i])
	{
		if (path[i]->flow != 0)
			path[i]->flow = 0;
		else
			path[i]->cap = -1;
		i += 1;
	}
}

int		path_repeated(t_paths *head, t_edge **tmp)
{
	int i;

	while (head)
	{
		i = 0;
		while (head->path[i] && tmp[i] && head->path[i] == tmp[i])
		{
			i += 1;
		}
		if (!head->path[i] && !tmp[i])
			return (1);
		head = head->next;
	}
	return (0);
}

int		path_goes_backwards(t_paths *head, t_edge **tmp)
{
	t_point p;
	int		p_len;

	p_len = plen(tmp);
	while (head)
	{
		p.x = 0;
		while (p.x < head->len)
		{
			p.y = 0;
			while (p.y < p_len)
			{
				if (head->path[p.x]->rev == tmp[p.y])
				{
					unvisit_path(head->path, head->path[p.x]);
					unvisit_path(tmp, head->path[p.x]);
					return (1);
				}
				p.y += 1;
			}
			p.x += 1;
		}
		head = head->next;
	}
	return (0);
}

t_edge	**make_path(t_edge **prev, int length, int dst)
{
	t_edge	**path;
	t_edge	*e;
	
	path = malloc(sizeof(t_edge *) * (length + 1));
	if (path == NULL)
	{
		ft_putendl_fd(ERROR_MALLOC, 2);
		exit(EXIT_FAILURE);
	}
	path[length--] = NULL;
	e = prev[dst];
	while (e != NULL)
	{
		path[length--] = e;
		e = prev[e->from];
	}
	return (path);
}

t_edge	**push_edge(t_edge **path, t_edge *new_edge)
{
	int		l;
	int		i;
	t_edge	**new;

	l = plen(path);
	new = malloc(sizeof(*new) * (l + 1));
	if (!new)
		return (NULL);
	i = 0;
	if (path)
	{
		while (path[i])
		{
			new[i] = path[i];
			i += 1;
		}
	}
	new[i++] = new_edge;
	new[i] = NULL;
	return (new);
}
