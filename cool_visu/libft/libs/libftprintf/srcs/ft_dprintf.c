/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbally <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 18:20:35 by hbally            #+#    #+#             */
/*   Updated: 2019/01/25 18:55:34 by hbally           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "ft_printf.h"
#include "libft.h"

int				ft_dprintf(int fd, const char *format, ...)
{
	va_list		args;
	t_index		params;

	if (!format)
		return (set_errno(NO_FMT_STRING));
	if (fd < 0)
		return (set_errno(BAD_FD));
	ft_bzero(&params, sizeof(t_index));
	va_start(args, format);
	params.fd = fd;
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
