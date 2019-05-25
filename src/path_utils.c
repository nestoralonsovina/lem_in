/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalonso <nalonso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 12:26:51 by nalonso           #+#    #+#             */
/*   Updated: 2019/05/25 17:46:42 by nalonso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	unvisit_path(t_edge **path, t_edge *intersection)
{
	int i;

	i = 0;
	while (path[i])
	{
		if (path[i] != intersection)
		{
			path[i]->visited = 0;
		}
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
	int	i;
	int	j;

	while (head)
	{
		i = 0;
		while (i < head->len)
		{
			j = 0;
			while (j < plen(tmp))
			{
				if (head->path[i]->rev == tmp[j])
				{
					unvisit_path(head->path, head->path[i]);
					unvisit_path(tmp, head->path[i]);
					return (1);
				}
				j += 1;
			}
			i += 1;
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
		ft_fprintf(2, "Error: Malloc couldn't allocate the necessary memory\n");
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
