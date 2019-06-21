/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_edges.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbally <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 16:15:43 by hbally            #+#    #+#             */
/*   Updated: 2019/03/19 16:16:51 by hbally           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lem_in.h"

void		ft_mid_file(t_wrap *wraper, int flag, t_list **lst)
{
	t_list	*tmp;

	if ((wraper->graph).source == NULL || (wraper->graph).sink == NULL)
		collector(wraper, KO);
	else
	{
		tmp = (*lst)->next;
		(*lst)->next = NULL;
		ft_free_list(tmp);
		collector(wraper, flag);
	}
}

void		ft_free_hop(t_node *node)
{
	t_list *hop;

	if (node->hop_data)
	{
		hop = node->hop_data;
		while (hop)
		{
			if (hop->content)
				ft_memdel((void**)&(hop->content));
			hop = hop->next;
		}
		del_all(&(node->hop_data));
	}
}

void		ft_get_edges(char **room_1, char **room_2, char *str,
							t_wrap *wraper)
{
	int len_1;
	int len_2;

	len_1 = ft_strclen(str, '-');
	if (!((*room_1) = ft_strcdup(str, '-')))
		collector(wraper, KO);
	len_1 = len_1 + 1;
	len_2 = ft_strlen(&str[len_1]);
	if (!((*room_2) = ft_strdup(&str[len_1])))
		collector(wraper, KO);
}

t_node		*ft_get_hashed(char *str, t_graph *graph)
{
	t_list	**tab;
	t_list	*lst;
	t_node	*node;
	int		index;

	index = hash((unsigned char *)str) % graph->table_size;
	tab = graph->nodes;
	lst = tab[index];
	if (!lst || lst == NULL)
		return (NULL);
	else
	{
		while (lst != NULL)
		{
			node = lst->content;
			if (ft_strcmp(node->name, str) == 0)
				return (node);
			lst = lst->next;
		}
	}
	return (NULL);
}

int			ft_add_edges(char **room_1, char **room_2, t_wrap *wraper,
							t_graph *graph)
{
	t_node *node;
	t_node *edge;

	if (!(node = ft_get_hashed(*room_1, graph)) || node == NULL)
	{
		free(*room_1);
		free(*room_2);
		return (0);
	}
	if (!(edge = ft_get_hashed(*room_2, graph)) || edge == NULL)
	{
		free(*room_1);
		free(*room_2);
		return (0);
	}
	add_start(wraper, edge, &node->edges);
	return (1);
}
