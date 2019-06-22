/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbally <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 16:21:04 by hbally            #+#    #+#             */
/*   Updated: 2019/03/19 16:21:22 by hbally           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "libft.h"

int		ft_count_nodes(char *line, int *nodes)
{
	int i;
	int count;
	int tiret;

	i = 0;
	count = 0;
	tiret = 0;
	while (line[i])
	{
		if (line[i] == ' ')
			count++;
		if (line[i] == '-')
			tiret++;
		i++;
	}
	if (count == 2 && tiret == 0)
	{
		(*nodes)++;
		return (1);
	}
	if (tiret == 1)
		return (2);
	return (1);
}

int		ft_is_node(char *line, t_wrap *wraper)
{
	int i;
	int count;
	int tiret;

	i = 0;
	count = 0;
	tiret = 0;
	while (line[i])
	{
		if (line[0] == 'L')
			collector(wraper, KO);
		if (line[i] == ' ')
			count++;
		if (line[i] == '-')
			tiret++;
		i++;
	}
	if (count == 2 && tiret == 0)
		return (1);
	else if (((tiret > 0 && count == 2) || (count != 2 && count != 0))
	&& line[0] != '#')
		collector(wraper, KO);
	return (0);
}

int		ft_is_link(char *line, t_wrap *wraper, t_list **prec)
{
	int i;
	int count;
	int tiret;

	i = 0;
	count = 0;
	tiret = 0;
	while (line[i])
	{
		if (line[i] == '-')
			tiret++;
		i++;
	}
	if (tiret == 1)
		return (1);
	else if (tiret > 1)
		ft_mid_file(wraper, DONE, prec);
	return (0);
}

int		ft_read_standard(t_wrap *wraper)
{
	int		ret;
	char	*line;
	t_list	*start;
	int		i;
	int		nodes;

	i = 0;
	nodes = 0;
	line = NULL;
	start = NULL;
	while ((ret = get_next_line(0, &line)) > 0)
	{
		if (i == 0)
		{
			ft_ants(line, wraper, 1);
			i++;
		}
		add_end(wraper, line, &start, &wraper->input_end);
		if (i == 1)
			i = ft_count_nodes(line, &nodes);
	}
	wraper->input_start = start;
	return (nodes);
}

int		ft_read_map(t_wrap *wraper, t_graph *graph)
{
	int size;

	size = ft_read_standard(wraper);
	ft_make_graph(wraper, size, graph);
	if (graph->source == NULL || graph->sink == NULL)
		collector(wraper, KO);
	return (0);
}
