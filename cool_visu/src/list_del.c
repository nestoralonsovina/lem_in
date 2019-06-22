/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_del.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbally <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 16:20:50 by hbally            #+#    #+#             */
/*   Updated: 2019/03/19 16:20:53 by hbally           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lem_in.h"

void					del_one(t_list *elem, t_list **start)
{
	t_list				*parse;

	if (elem && start && *start)
	{
		elem->content = NULL;
		if (*start == elem)
		{
			*start = (*start)->next;
			ft_memdel((void**)&elem);
		}
		else
		{
			parse = *start;
			while (parse->next != elem)
				parse = parse->next;
			parse->next = elem->next;
			elem->next = NULL;
			ft_memdel((void**)&elem);
		}
	}
}

void					del_all(t_list **start)
{
	if (start)
	{
		while (*start)
			del_one(*start, start);
	}
}
