/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultoxa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbally <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 10:10:36 by hbally            #+#    #+#             */
/*   Updated: 2018/11/16 10:30:23 by hbally           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char				*ft_ultoxa(unsigned long n, int upper)
{
	unsigned long	d;
	size_t			len;
	char			*ret;

	len = 0;
	if (n == 0)
		return (ft_itoa(0));
	if (!(ret = ft_strnew(len)))
		return (NULL);
	d = 0x10ul << ((sizeof(long) - 1) * 8);
	while (n / d == 0)
		d = d >> 4;
	while (d != 0)
	{
		if (!(ret = ft_str_realloc(ret, ++len)))
			return (NULL);
		ret[len - 1] = '0' + (n / d < 10 ? n / d : 39 - (32 * upper) + n / d);
		n -= d * (n / d);
		d = d >> 4;
	}
	return (ret);
}
