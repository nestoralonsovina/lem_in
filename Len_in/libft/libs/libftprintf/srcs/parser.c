/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbally <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 14:09:48 by hbally            #+#    #+#             */
/*   Updated: 2019/01/17 17:25:49 by hbally           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "ft_printf.h"
#include "libft.h"

int					parser(const char *format, t_index *params, va_list *args)
{
	params->fmt_head++;
	params->precision = -1;
	while (format[params->fmt_head])
	{
		if (!check_flag(format[params->fmt_head], params) &&
			!check_width(format, &(params->fmt_head), params, args) &&
			!check_precision(format, &(params->fmt_head), params) &&
			!check_length(format, &(params->fmt_head), params) &&
			dispatcher(format[params->fmt_head], args, params) == ARG_FOUND)
		{
			return (ARG_FOUND);
		}
		params->fmt_head++;
	}
	params->fmt_head--;
	return (0);
}
