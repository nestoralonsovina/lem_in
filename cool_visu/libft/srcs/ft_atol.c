/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbally <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 20:00:42 by hbally            #+#    #+#             */
/*   Updated: 2018/12/31 12:06:53 by hbally           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long			ft_atol(const char *str)
{
	int			i;
	long		sign;
	long		ret;
	long		previous;

	i = 0;
	sign = 1;
	ret = 0;
	previous = 0;
	while ((str[i] >= 7 && str[i] <= 13) || str[i] == ' ')
		i++;
	sign = str[i] == '-' ? -1 : 1;
	i += (str[i] == '+' || str[i] == '-') ? 1 : 0;
	while (ft_isdigit(str[i]))
	{
		ret = ret * 10 + (str[i] - '0');
		if ((ret < previous) && (ret < 0 && sign == -1 ? (ret - 1) < 0 : 1))
			return (0L);
		previous = ret;
		i++;
	}
	return (ret * sign);
}
