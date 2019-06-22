/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbally <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 12:56:07 by hbally            #+#    #+#             */
/*   Updated: 2019/01/25 18:48:17 by hbally           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "ft_printf.h"
#include "libft.h"

int				ft_printf(const char *format, ...)
{
	va_list		args;
	t_index		params;

	if (!format)
		return (set_errno(NO_FMT_STRING));
	ft_bzero(&params, sizeof(t_index));
	va_start(args, format);
	params.fd = 1;
	while (format[params.fmt_head])
	{
		if (format[params.fmt_head] == '%')
			printer_fmt(format, &params, &args);
		params.fmt_head++;
		reset(&params);
	}
	printer_fmt(format, &params, &args);
	va_end(args);
	return (exit_clean(NULL, &params));
}
