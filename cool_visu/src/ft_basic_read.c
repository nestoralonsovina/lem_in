/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_basic_read.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbally <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 16:11:31 by hbally            #+#    #+#             */
/*   Updated: 2019/03/19 17:51:59 by hbally           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lem_in.h"

int					ft_nbr_size(int nbr)
{
	int len;

	len = 1;
	while (nbr > 9)
	{
		nbr = nbr / 10;
		len++;
	}
	return (len);
}

int					ft_ants(char *line, t_wrap *wraper, int ants)
{
	int x;
	int len;
	int new_len;

	x = 0;
	while (line[x])
	{
		if ((line[x] < '0' || line[x] > '9') && line[x] != ' ')
			collector(wraper, KO);
		x++;
	}
	len = ft_strclen(line, ' ');
	x = ft_atoi(line);
	new_len = ft_nbr_size(x);
	if (len != new_len)
		collector(wraper, KO);
	if (ants == 1 && x <= 0)
		collector(wraper, KO);
	return (x);
}

unsigned long		hash(unsigned char *str)
{
	unsigned long	hash;
	int				c;

	hash = 5381;
	while ((c = *str++))
		hash = ((hash << 5) + hash) + c;
	return (hash);
}

int					ft_is_comment(t_wrap *wraper, char *str, int past)
{
	if (ft_strcmp(str, "##start") == 0 && past == 0)
		return (1);
	else if (ft_strcmp(str, "##end") == 0 && past == 0)
		return (2);
	if (ft_strcmp(str, "##start") == 0 && past != 0)
		collector(wraper, KO);
	if (ft_strcmp(str, "##end") == 0 && past != 0)
		collector(wraper, KO);
	return (past);
}

void				ft_insert_in_tab(t_wrap *wraper, t_graph *graph, int index,
										t_node *new_node)
{
	t_list **tab;
	t_node *node;

	tab = graph->nodes;
	node = ft_get_hashed(new_node->name, graph);
	if (node == NULL)
		add_start(wraper, new_node, &tab[index]);
	else
		collector(wraper, KO);
}
