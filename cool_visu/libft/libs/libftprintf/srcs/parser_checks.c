/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_checks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbally <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/29 15:31:06 by hbally            #+#    #+#             */
/*   Updated: 2019/01/17 14:16:35 by hbally           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

/*
** Flag is represented as a bit code
** ...00001 > #
** ...00010 > 0
** ...00100 > -
** ...01000 > sp
** ...10000 > +
*/

int				check_flag(const char c, t_index *params)
{
	if (c == '#')
		return (params->flags |= 0x1);
	if (c == '0')
		return (params->flags |= 0x2);
	if (c == '-')
		return (params->flags |= 0x4);
	if (c == ' ')
		return (params->flags |= 0x8);
	if (c == '+')
		return (params->flags |= 0x10);
	return (0);
}

/*
** Length is represented as a bit code
** ...00001 > hh
** ...00010 > h
** ...00100 > ll
** ...01000 > l
** ...10000 > L
*/

int				check_length(const char *format,
								size_t *head,
								t_index *params)
{
	if (format[*head] == 'h' && format[*head + 1] == 'h')
	{
		(*head)++;
		return (params->length |= 0x1);
	}
	if (format[*head] == 'h')
		return (params->length |= 0x2);
	if (format[*head] == 'l' && format[*head + 1] == 'l')
	{
		(*head)++;
		return (params->length |= 0x4);
	}
	if (format[*head] == 'l')
		return (params->length |= 0x8);
	if (format[*head] == 'L')
		return (params->length |= 0x10);
	return (0);
}

int				check_width(const char *format,
							size_t *head,
							t_index *params,
							va_list *args)
{
	if (ft_isdigit(format[*head]))
	{
		params->width = ft_atoll(&(format[*head]));
		while (ft_isdigit(format[*head + 1]))
			(*head)++;
		return (1);
	}
	if (format[*head] == '*')
	{
		params->width = (long long)va_arg(*args, unsigned int);
		return (1);
	}
	return (0);
}

int				check_precision(const char *format,
								size_t *head,
								t_index *params)
{
	if (format[*head] == '.')
	{
		if (ft_isdigit(format[*head + 1]))
		{
			params->precision = ft_atoll(&(format[*head + 1]));
			while (ft_isdigit(format[*head + 1]))
				(*head)++;
		}
		else
			params->precision = 0;
		return (1);
	}
	return (0);
}
