/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_mapdata.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbally <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 16:21:38 by hbally            #+#    #+#             */
/*   Updated: 2019/03/19 16:22:11 by hbally           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "libft.h"

void		output_mapdata(t_list *input)
{
	t_list	*elem;

	elem = input;
	while (elem)
	{
		ft_printf("%s\n", ((char*)(elem->content)));
		elem = elem->next;
	}
	ft_printf("\n");
}
