/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   baker_integers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbally <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/22 15:17:03 by hbally            #+#    #+#             */
/*   Updated: 2019/01/17 16:56:45 by hbally           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf.h"
#include "libft.h"

/*
** Length is represented as a bit code
** ...00001 > hh (1)
** ...00010 > h (2)
** ...00100 > ll (4)
** ...01000 > l (8)
** ...10000 > L (10)
*/

static int		check_downcast(int n, t_index *params)
{
	if (params->type == 'd' || params->type == 'i')
	{
		if (params->length & 0x1)
			n = (char)n;
		else if (params->length & 0x2)
			n = (short)n;
	}
	else
	{
		if (params->length & 0x1)
			n = (unsigned char)n;
		else if (params->length & 0x2)
			n = (unsigned short)n;
	}
	return (n);
}

int				baker_int(int n, t_index *params)
{
	char			*result;

	n = check_downcast(n, params);
	if (params->type == 'u')
		result = ft_uitoa((unsigned int)n);
	else if (params->type == 'd' || params->type == 'i' || n == 0)
	{
		if (n < 0)
			params->negative = 1;
		result = ft_uitoa((unsigned int)(n >= 0 ? n : -n));
	}
	else if (params->type == 'x' || params->type == 'X')
		result = ft_uitoxa((unsigned int)n, (int)(params->type == 'X'));
	else
		result = ft_uitooa((unsigned int)n);
	if (result)
	{
		params->size = ft_strlen(result);
		printer_arg(result, params->type, params);
		free(result);
	}
	else
		params->error = 1;
	return (0);
}
