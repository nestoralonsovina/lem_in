/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_clean.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbally <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 16:00:29 by hbally            #+#    #+#             */
/*   Updated: 2019/01/25 18:46:57 by hbally           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include "ft_printf.h"
#include "libft.h"

int				set_errno(int error)
{
	if (error == NO_FMT_STRING)
		errno = EINVAL;
	if (error == BAD_FD)
		errno = EBADF;
	return (-1);
}

int				exit_clean(char **ret, t_index *params)
{
	if (ret && params->buf && !params->error)
		*ret = params->buf;
	if (params->error && params->buf)
		ft_memdel((void**)&(params->buf));
	if (!params->error)
		return (params->head);
	else
		return (-1);
}
