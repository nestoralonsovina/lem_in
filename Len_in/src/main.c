/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbally <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 16:22:31 by hbally            #+#    #+#             */
/*   Updated: 2019/03/20 14:22:12 by hbally           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "libft.h"
#include <unistd.h>

void			stdout_wrapper(t_wrap *wrap, t_graph *graph)
{
	output_mapdata(wrap->input_start);
	if (graph->source_capacity > 0)
		output_result(wrap,
					graph->source,
					graph->flow_best,
					graph->source_capacity);
}

uint8_t			tofile_wrapper(t_wrap *wrap, t_graph *graph)
{
	if (create_file(wrap, "viz/data/turns_data.js")
			|| create_file(wrap, "turns_data.js"))
	{
		stdout_wrapper(wrap, graph);
		close(wrap->out_fd);
		if (create_file(wrap, "viz/data/graph_data.js")
				|| create_file(wrap, "graph_data.js"))
		{
			graph_to_file(wrap, graph);
			close(wrap->out_fd);
			return (0);
		}
	}
	collector(wrap, KO);
	return (1);
}

void			output_wrapper(t_wrap *wrap, t_graph *graph)
{
	flow_create_all(wrap, graph);
	if (graph->flow_best)
	{
		if (wrap->opt.dict.export)
			tofile_wrapper(wrap, graph);
		else
			stdout_wrapper(wrap, graph);
	}
	else
		collector(wrap, KO);
}

void			input_wrapper(int argc, char **argv,
								t_wrap *wrap, t_graph *graph)
{
	get_options(&(wrap->opt), argc, argv);
	ft_read_map(wrap, graph);
}

int				main(int argc, char **argv)
{
	t_wrap		wrap;

	ft_bzero(&wrap, sizeof(t_wrap));
	input_wrapper(argc, argv, &wrap, &(wrap.graph));
	output_wrapper(&wrap, &(wrap.graph));
	collector(&wrap, OK);
	return (0);
}
