/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalonso <nalonso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 12:26:51 by nalonso           #+#    #+#             */
/*   Updated: 2019/06/15 14:53:57 by nalonso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

t_edge	**make_path(t_edge **prev, int length, int dst)
{
	t_edge	**path;
	t_edge	*e;

	path = gb_malloc(&g_gb, sizeof(t_edge *) * (length + 1));
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
