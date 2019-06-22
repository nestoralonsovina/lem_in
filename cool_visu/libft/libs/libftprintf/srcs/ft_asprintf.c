/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_asprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbally <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 14:13:13 by hbally            #+#    #+#             */
/*   Updated: 2019/01/25 18:34:33 by hbally           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "ft_printf.h"
#include "libft.h"

int				ft_asprintf(char **ret, const char *format, ...)
{
	va_list		args;
	t_index		params;

	ft_bzero(&params, sizeof(t_index));
	if (!ret || !format || !(params.buf = ft_strnew(0)))
		return (-1);
	params.asprintf = 1;
	va_start(args, format);
	while (format[params.fmt_head])
	{
		if (format[params.fmt_head] == '%')
			printer_fmt(format, &params, &args);
		reset(&params);
		params.fmt_head++;
	}
	printer_fmt(format, &params, &args);
	va_end(args);
	return (exit_clean(ret, &params));
}
