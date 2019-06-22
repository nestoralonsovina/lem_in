/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ulltoa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbally <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 10:10:36 by hbally            #+#    #+#             */
/*   Updated: 2018/12/31 16:09:17 by hbally           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

char				*ft_ulltoa(unsigned long long n)
{
	size_t			len;
	char			*ret;

	len = 0;
	if (!(ret = ft_strnew(len)))
		return (NULL);
	while (n != 0 || !len)
	{
		if (!(ret = ft_str_realloc(ret, ++len)))
			return (NULL);
		ft_memmove(&ret[1], &ret[0], len);
		ret[0] = '0' + (n % 10ull);
		n /= 10ull;
	}
	return (ret);
}
