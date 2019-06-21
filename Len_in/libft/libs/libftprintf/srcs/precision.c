/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbally <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/31 11:53:04 by hbally            #+#    #+#             */
/*   Updated: 2019/01/14 12:00:52 by hbally           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

size_t				find_point(const char *s)
{
	size_t			pos;

	pos = 0;
	while (s[pos] && s[pos] != '.')
		pos++;
	return (pos);
}

int					float_precision(const char *s, t_index *params)
{
	size_t			point_pos;
	long long		to_add;

	point_pos = find_point(s);
	if (point_pos == params->size &&
			(params->precision != 0 ||
			(params->precision == 0 && params->flags & 0x1)))
		write_buff(".", 1, params);
	if (params->precision == 0)
		return (0);
	else if (params->precision != 0 && point_pos == params->size)
		printer_filler('0', params->precision, params);
	else
	{
		to_add = params->precision - (params->size - (point_pos + 1));
		printer_filler('0', to_add > 0 ? to_add : 0, params);
	}
	return (0);
}

void				int_precision(t_index *params)
{
	if (params->precision != -1 &&
			params->precision > (long long)params->size)
		printer_filler('0', params->precision - params->size, params);
}
