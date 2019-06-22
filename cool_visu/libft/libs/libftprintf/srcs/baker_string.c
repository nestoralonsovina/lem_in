/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   baker_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbally <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/29 14:57:20 by hbally            #+#    #+#             */
/*   Updated: 2019/02/08 10:15:25 by hbally           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

int				baker_string(char *s, t_index *params)
{
	char		error_handler[7];

	if (!s)
	{
		ft_strcpy(error_handler, "(null)");
		params->size = 6;
		if (params->precision != -1 &&
				params->precision < (long long)params->size)
			params->size = params->precision;
		printer_arg(error_handler, params->type, params);
		return (0);
	}
	params->size = ft_strlen(s);
	if (params->precision != -1 &&
			params->precision < (long long)params->size)
		params->size = params->precision;
	printer_arg(s, params->type, params);
	return (0);
}
