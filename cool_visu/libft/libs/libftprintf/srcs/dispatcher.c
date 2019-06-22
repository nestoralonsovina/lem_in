/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatcher.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbally <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/31 11:38:52 by hbally            #+#    #+#             */
/*   Updated: 2019/01/17 17:26:25 by hbally           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "ft_printf.h"

/*
** Length is represented as a bit code
** ...00001 > hh (1)
** ...00010 > h (2)
** ...00100 > ll (4)
** ...01000 > l (8)
** ...10000 > L (10)
*/

static int		dispatcher_integer(char c, va_list *args, t_index *params)
{
	if (c == 'f')
	{
		if (params->length & 0x10)
			return (baker_longdouble(va_arg(*args, long double), params));
		return (baker_double(va_arg(*args, double), params));
	}
	return (NO_ARG_FOUND);
}

static int		dispatcher_double(char c, va_list *args, t_index *params)
{
	if (c == 'p')
		return (baker_pointer(va_arg(*args, void*), params));
	if (c == 'd' || c == 'i' || c == 'o' || c == 'x' || c == 'X' || c == 'u')
	{
		if (params->length & 0x4)
			return (baker_longlong(va_arg(*args, long long), params));
		if (params->length & 0x8)
			return (baker_long(va_arg(*args, long), params));
		return (baker_int(va_arg(*args, int), params));
	}
	return (NO_ARG_FOUND);
}

static int		dispatcher_str(char c, va_list *args, t_index *params)
{
	if (c == '%')
	{
		params->type = 'c';
		return (baker_char('%', params));
	}
	if (c == 'c')
		return (baker_char(va_arg(*args, int), params));
	if (c == 's')
		return (baker_string(va_arg(*args, char*), params));
	return (NO_ARG_FOUND);
}

int				dispatcher(char c, va_list *args, t_index *params)
{
	params->type = c;
	if (dispatcher_str(c, args, params) == ARG_FOUND ||
		dispatcher_integer(c, args, params) == ARG_FOUND ||
		dispatcher_double(c, args, params) == ARG_FOUND)
		return (ARG_FOUND);
	params->type = '\0';
	return (NO_ARG_FOUND);
}
