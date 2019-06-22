/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   width.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbally <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/31 12:03:12 by hbally            #+#    #+#             */
/*   Updated: 2019/01/14 12:51:17 by hbally           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		print_width(t_index *params, long long to_print, int print)
{
	char		c;

	c = ' ';
	if (to_print < 0)
		return (0);
	if ((!(params->flags & 0x4) && params->flags & 0x2) &&
		(params->type == 'f' || params->type == 's' || params->type == 'c' ||
		(params->type != 'f' && params->precision == -1)))
		c = '0';
	if (print)
		printer_filler(c, to_print, params);
	return (to_print);
}

int				width(const char *s, const char c, t_index *params, int print)
{
	long long	to_print;

	to_print = params->width;
	to_print -= prefix(params, s, c, 0);
	if (c == 'f')
	{
		if ((params->precision == 0 && params->flags & 0x1) ||
				params->precision != 0)
			to_print--;
		to_print -= find_point(s);
		to_print -= params->precision != -1 ? params->precision : 6;
	}
	else
	{
		if (c != 's' && c != 'c' && params->precision != -1 &&
				params->precision > (long long)params->size)
			to_print -= params->precision;
		else
			to_print -= params->size;
	}
	return (print_width(params, to_print, print));
}
