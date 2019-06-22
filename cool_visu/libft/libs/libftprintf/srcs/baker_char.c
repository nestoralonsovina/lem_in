/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   baker_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbally <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/22 15:19:18 by hbally            #+#    #+#             */
/*   Updated: 2019/01/17 16:55:35 by hbally           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

int				baker_char(char c, t_index *params)
{
	params->size = 1;
	printer_arg(&c, params->type, params);
	return (0);
}
