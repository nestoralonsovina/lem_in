/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   baker_long.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbally <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/29 14:54:45 by hbally            #+#    #+#             */
/*   Updated: 2019/01/17 16:56:53 by hbally           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf.h"
#include "libft.h"

int				baker_long(long n, t_index *params)
{
	char			*result;

	if (params->type == 'u')
		result = ft_ultoa((unsigned long)n);
	else if (params->type == 'd' || params->type == 'i' || n == 0)
	{
		if (n < 0)
			params->negative = 1;
		result = ft_ultoa((unsigned long)(n >= 0 ? n : -n));
	}
	else if (params->type == 'x' || params->type == 'X')
		result = ft_ultoxa((unsigned long)n, (int)(params->type == 'X'));
	else
		result = ft_ultooa((unsigned long)n);
	if (result)
	{
		params->size = ft_strlen(result);
		printer_arg(result, params->type, params);
		free(result);
	}
	else
		params->error = 1;
	return (0);
}
