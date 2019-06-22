/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_result.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbally <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 16:47:36 by hbally            #+#    #+#             */
/*   Updated: 2019/03/20 12:01:57 by hbally           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "libft.h"

void				move_to_stdout(int counter, t_node *dest, int flag)
{
	static uint8_t	not_at_start;

	if (flag == TURN_END)
	{
		ft_printf("\n");
		not_at_start = 0;
	}
	else
	{
		if (not_at_start)
			ft_printf(" ");
		ft_printf("L%d-%s", counter, dest ? dest->name : NULL);
		not_at_start = 1;
	}
}

uint8_t				send(t_wrap *wrap, t_node *node, t_bfs *sim, int counter)
{
	t_gate_data		*data;

	data = get_data(node->gate_data, wrap->graph.flow_best);
	if (data && data->crowding && data->sent < data->crowding)
	{
		data->sent++;
		node->guest = counter;
		if (node->type != END)
			add_end(wrap, (void*)node, &(sim->frontier), &(sim->frontier_end));
		move_to_stdout(counter, node, 0);
		if (wrap->opt.dict.export)
			move_to_file(wrap, wrap->graph.source, node, counter);
		return (1);
	}
	return (0);
}

void				push(t_wrap *wrap, int flow, t_bfs *sim)
{
	t_node			*node;
	t_node			*dest;

	while (sim->level)
	{
		node = ((t_node*)(sim->level->content));
		dest = hop_get_flow(node->hop_data, flow);
		dest->guest = node->guest;
		if (dest->type != END)
			add_end(wrap, (void*)dest, &(sim->frontier), &(sim->frontier_end));
		move_to_stdout(node->guest, dest, 0);
		if (wrap->opt.dict.export)
			move_to_file(wrap, node, dest, node->guest);
		del_one(sim->level, &(sim->level));
	}
}

void				turn_control(t_wrap *wrap, int flag)
{
	static int		turn_number;

	if (wrap->opt.dict.export)
		move_to_file(wrap, 0, 0, flag);
	if (flag <= TURN_END)
		move_to_stdout(0, 0, TURN_END);
	if (flag == TURN_START)
		turn_number++;
	if (flag == LAST_TURN_END && wrap->opt.dict.verbose)
	{
		ft_printf("\n%-40s : %d\n", "Ants at start",
					wrap->graph.source_capacity);
		ft_printf("%-40s : %d\n", "Number of Ford-Fulkerson iterations",
					wrap->graph.flow_max - 1);
		ft_printf("%-40s : %d\n", "Chosen iteration",
					wrap->graph.flow_best);
		ft_printf("%-40s : %d\n\n", "Total number of lines printed",
					turn_number);
	}
}

void				output_result(t_wrap *wrap, t_node *source,
									int flow, int remain)
{
	t_bfs			sim;
	t_list			*edge;
	int				counter;

	ft_bzero((void*)&sim, sizeof(t_bfs));
	wrap->bfs_state = &sim;
	counter = 0;
	while (!counter || update_level(&(sim.level), &(sim.frontier)) || remain)
	{
		turn_control(wrap, TURN_START);
		edge = source->edges;
		push(wrap, flow, &sim);
		while (edge && remain)
		{
			if (send(wrap, (t_node*)(edge->content), &sim, counter + 1))
			{
				counter++;
				remain--;
			}
			edge = edge->next;
		}
		turn_control(wrap, sim.frontier || remain ? TURN_END : LAST_TURN_END);
	}
	wrap->bfs_state = NULL;
}
