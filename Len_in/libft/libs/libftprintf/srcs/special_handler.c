/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbally <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/04 10:47:32 by hbally            #+#    #+#             */
/*   Updated: 2019/01/04 10:48:56 by hbally           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		special_handler(const char *s, const char c, t_index *params)
{
	if (c != 's' && c != 'c' && c != 'f')
	{
		if (c == 'o')
		{
			if (params->flags & 0x1)
				if ((params->precision > (long long)params->size) ||
						(!(params->flags & 0x4) && params->flags & 0x2 &&
						params->precision == -1 &&
						width(s, c, params, 0) > 0) ||
						(params->precision != 0 && s[0] == '0'))
					params->flags -= 0x1;
		}
		if (s[0] == '0' && (c == 'x' || c == 'X') && params->flags & 0x1)
			params->flags -= 0x1;
		if (s[0] == '0' && params->precision == 0)
			params->size = 0;
	}
}
