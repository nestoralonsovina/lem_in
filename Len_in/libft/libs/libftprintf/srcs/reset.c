/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbally <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 14:53:58 by hbally            #+#    #+#             */
/*   Updated: 2019/01/25 18:16:04 by hbally           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

void			reset(t_index *params)
{
	t_index		tmp;

	tmp = *params;
	ft_bzero(params, sizeof(t_index));
	params->asprintf = tmp.asprintf;
	params->fd = tmp.fd;
	params->buf = tmp.buf;
	params->head = tmp.head;
	params->head_old = tmp.head_old;
	params->fmt_head = tmp.fmt_head;
	params->fmt_head_old = tmp.fmt_head_old;
}
