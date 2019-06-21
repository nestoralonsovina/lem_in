/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lltoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbally <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/31 12:11:32 by hbally            #+#    #+#             */
/*   Updated: 2018/12/31 12:11:40 by hbally           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				*ft_lltoa(long long n)
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
		ret[!neg ? 0 : 1] = '0' + (!neg ? (n % 10ll) : (-1 * (n % 10ll)));
		n /= 10ll;
	}
	return (ret);
}
