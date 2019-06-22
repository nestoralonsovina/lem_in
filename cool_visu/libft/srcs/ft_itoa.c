/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbally <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 10:10:36 by hbally            #+#    #+#             */
/*   Updated: 2018/11/16 10:30:23 by hbally           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

char				*ft_itoa(int n)
{
	size_t			len;
	int				neg;
	char			*ret;

	len = 0;
	neg = n < 0 ? 1 : 0;
	if (!(ret = ft_strnew(!neg ? len : ++len)))
		return (NULL);
	if (neg)
		ret[0] = '-';
	while (n != 0 || !len)
	{
		if (!(ret = ft_str_realloc(ret, ++len)))
			return (NULL);
		ft_memmove(&ret[!neg ? 1 : 2], !neg ? &ret[0] : &ret[1], len);
		ret[!neg ? 0 : 1] = '0' + (!neg ? (n % 10) : (-1 * (n % 10)));
		n /= 10;
	}
	return (ret);
}
