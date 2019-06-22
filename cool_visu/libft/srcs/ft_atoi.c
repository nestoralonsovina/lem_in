/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbally <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 20:00:42 by hbally            #+#    #+#             */
/*   Updated: 2019/02/08 10:13:24 by hbally           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		get_number(const char *str, size_t i, int sign)
{
	size_t		len;
	int			n;

	n = 0;
	len = 0;
	while (ft_isdigit(str[i]))
	{
		if (len == 9 && (n * 10 < 0 || str[i] >= ('9' - (sign == 1))))
			return (0);
		n = n * 10 + (str[i] - '0');
		i++;
		len++;
	}
	return (n * sign);
}

int				ft_atoi(const char *str)
{
	size_t		i;
	size_t		len;
	int			sign;

	i = 0;
	while ((str[i] >= 7 && str[i] <= 13) || str[i] == ' ')
		i++;
	sign = str[i] == '-' ? -1 : 1;
	i += (str[i] == '+' || str[i] == '-') ? 1 : 0;
	len = i;
	while (ft_isdigit(str[len]))
		len++;
	len = len - i;
	if (len < 1 || len > 10 || (len == 10 && str[i] > '2'))
		return (0);
	return (get_number(str, i, sign));
}
