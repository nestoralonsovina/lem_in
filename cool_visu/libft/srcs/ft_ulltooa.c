/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ulltooa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbally <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 10:10:36 by hbally            #+#    #+#             */
/*   Updated: 2018/12/31 16:09:49 by hbally           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char					*ft_ulltooa(unsigned long long n)
{
	unsigned long long	digit;
	size_t				len;
	char				*ret;

	len = 0;
	if (n == 0)
		return (ft_itoa(0));
	if (!(ret = ft_strnew(len)))
		return (NULL);
	digit = 01ull;
	while ((digit | digit << 1 | digit << 2) < n)
		digit |= (digit << 1 | digit << 2 | digit << 3);
	digit -= digit >> 1;
	while (digit != 0)
	{
		if (!(ret = ft_str_realloc(ret, ++len)))
			return (NULL);
		ret[len - 1] = '0' + n / digit;
		n -= digit * (n / digit);
		digit /= 010ull;
	}
	return (ret);
}
