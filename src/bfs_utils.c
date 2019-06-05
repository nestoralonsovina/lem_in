/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalonso <nalonso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 17:45:47 by nalonso           #+#    #+#             */
/*   Updated: 2019/06/02 16:02:06 by jallen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"




void	free_paths(t_paths *head)
{
	t_paths *tmp;
	int		i;
	int		j;

	while (head)
	{
		tmp = head->next;
		free(head->path);
		i = 0;
		j = head->move[0]->len;
		while (i < j)
		{
			free(head->move[i]);
			i += 1;
		}
		free(head->move);
		free(head);
		head = tmp;
	}
}
