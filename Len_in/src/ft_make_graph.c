/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_graph.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbally <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 16:20:26 by hbally            #+#    #+#             */
/*   Updated: 2019/03/19 16:20:41 by hbally           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "libft.h"

void		ft_make_tab(int size, t_wrap *wraper, t_graph *graph)
{
	int	i;

	i = 0;
	if (!(graph->nodes = (t_list **)ft_memalloc(sizeof(t_list *) * size)))
		collector(wraper, KO);
	graph->table_size = size;
}

void		ft_get_coord(char *str, t_node **node, t_wrap *wraper)
{
	int			i;
	t_vector	coord;

	i = 0;
	while (str[i] != ' ')
		i++;
	i++;
	coord.x = ft_ants(&str[i], wraper, 0);
	while (str[i] != ' ')
		i++;
	i++;
	coord.y = ft_ants(&str[i], wraper, 0);
	(*node)->coord = coord;
}

void		ft_make_node(t_wrap *wraper, char *str, t_graph *graph, int *type)
{
	t_node	*new_node;
	int		index;

	new_node = (t_node *)ft_memalloc(sizeof(t_node));
	if (!((new_node->name = ft_strcdup(str, ' '))))
		collector(wraper, KO);
	new_node->type = *type;
	ft_get_coord(str, &new_node, wraper);
	index = hash((unsigned char *)new_node->name) % graph->table_size;
	ft_insert_in_tab(wraper, graph, index, new_node);
	if (*type == START && graph->source == NULL)
		graph->source = new_node;
	else if (*type == START && graph->source != NULL)
		collector(wraper, KO);
	if (*type == END && graph->sink == NULL)
		graph->sink = new_node;
	else if (*type == END && graph->sink != NULL)
		collector(wraper, KO);
	*type = 0;
}

void		ft_add_link(t_wrap *wraper, char *str, t_graph *graph, t_list **lst)
{
	char	*room_1;
	char	*room_2;

	ft_get_edges(&room_1, &room_2, str, wraper);
	if (ft_strcmp(room_1, room_2) == 0)
		ft_mid_file(wraper, DONE, lst);
	if (!(ft_add_edges(&room_1, &room_2, wraper, graph)))
		ft_mid_file(wraper, DONE, lst);
	if (!(ft_add_edges(&room_2, &room_1, wraper, graph)))
		ft_mid_file(wraper, DONE, lst);
	free(room_1);
	free(room_2);
}

int			ft_make_graph(t_wrap *wraper, int size, t_graph *graph)
{
	int		i;
	t_list	*input;
	int		flag;
	t_list	*prec;

	i = 0;
	flag = 0;
	input = wraper->input_start;
	ft_make_tab(size, wraper, graph);
	while (input != NULL)
	{
		if (i++ == 0)
			graph->source_capacity = ft_ants(input->content, wraper, 1);
		else if (((char *)input->content)[0] == '#')
			flag = ft_is_comment(wraper, input->content, flag);
		else if (ft_is_node(input->content, wraper))
			ft_make_node(wraper, input->content, graph, &flag);
		else if (ft_is_link(input->content, wraper, &prec))
			ft_add_link(wraper, input->content, graph, &prec);
		else
			ft_mid_file(wraper, DONE, &prec);
		prec = input;
		input = input->next;
	}
	return (0);
}
