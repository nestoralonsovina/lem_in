/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mv_visu.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalonso <nalonso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 20:28:59 by jallen            #+#    #+#             */
/*   Updated: 2019/06/23 18:20:47 by jallen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

static int	check_next(t_path **path, int len, int predicted, int *move)
{
	*move = 1;
	if (predicted > 0)
	{
		ft_putchar(' ');
		return (1);
	}
	while (len > 0)
	{
		if (path[len]->room->ant > 0)
		{
			ft_putchar(' ');
			return (1);
		}
		len--;
	}
	return (0);
}

static int	next_path(t_path **path, int len, int predicted)
{
	int i;

	i = 0;
	if (predicted > 0)
		return (1);
	while (i < len)
	{
		if (path[i]->room->ant > 0)
			return (1);
		i++;
	}
	return (0);
}

static void	min_len(t_path **path, int nb_ant, int *move, t_paths *head)
{
	if (head->len == 1 && path[0]->room->ant > 0 &&
			(int)head->predicted_ants > 0)
	{
		path[1]->room->ant += 1;
		ft_printf("L%d-%s", nb_ant - path[0]->room->ant + 1,
				path[1]->room->name);
		path[0]->room->ant -= 1;
		*move = 1;
	}
}

static void	move_ant(t_path **path, int nb_ant, int *move, t_paths *head)
{
	int i;

	i = head->len;
	min_len(path, nb_ant, move, head);
	while (--i > 0)
	{
		if (path[i]->room->ant > 0)
		{
			path[i + 1]->room->ant = (i + 1 == head->len)
				? path[i + 1]->room->ant + 1 : path[i]->room->ant;
			ft_printf("L%d-%s-%s", path[i]->room->ant, path[i - 1]->room->name,\
					path[i + 1]->room->name);
			path[i]->room->ant = 0;
			check_next(path, i, (int)head->predicted_ants, move);
		}
		if (i == 1 && path[1]->room->ant == 0
				&& path[0]->room->ant > 0 && (int)head->predicted_ants > 0)
		{
			path[1]->room->ant = nb_ant - path[0]->room->ant + 1;
			ft_printf("L%d-%s-%s", path[1]->room->ant, path[0]->room->name,\
					path[1]->room->name);
			path[0]->room->ant -= 1;
			*move = 1;
		}
	}
}

/*
** Function: make_movements
** function to initialize the path and loop till the end
*/

void		play_visu(t_graph *g, t_paths *head, int debug)
{
	t_paths		*ptr;
	t_counters	c;

	c.cnt = 0;
	g->adj_list[g->source.index]->ant = g->nb_ant;
	while (head->move[head->len]->room->ant != g->nb_ant)
	{
		ptr = head;
		c.sp = 0;
		while (ptr)
		{
			c.move = 0;
			move_ant(ptr->move, g->nb_ant, &c.move, ptr);
			ptr->predicted_ants -= 1;
			c.sp++;
			ptr = ptr->next;
			if (ptr && next_path(ptr->move, ptr->len, (int)ptr->predicted_ants)
					&& c.sp >= 1 && c.move == 1
					&& head->move[head->len]->room->ant != g->nb_ant)
				ft_putchar(' ');
		}
		ft_putendl(0);
		c.cnt++;
	}
	info_paths(head, g, c.cnt, debug);
}
