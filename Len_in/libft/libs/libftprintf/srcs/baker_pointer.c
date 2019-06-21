/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   baker_pointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbally <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/29 14:56:23 by hbally            #+#    #+#             */
/*   Updated: 2019/01/17 16:57:16 by hbally           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf.h"
#include "libft.h"

/*
** Length is represented as a bit code
** ...00001 > hh
** ...00010 > h
** ...00100 > ll
** ...01000 > l
** ...10000 > L
*/

int				baker_pointer(void *p, t_index *params)
{
	params->type = 'x';
	if (!p)
	{
		ft_putstr("0x");
		baker_int(0, params);
	}
	else
	{
		params->flags |= 0x1;
		params->length |= 0x8;
		baker_long((unsigned long)p, params);
	}
	return (0);
}
