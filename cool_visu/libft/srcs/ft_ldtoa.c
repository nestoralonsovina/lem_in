/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ldtoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbally <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/04 10:44:59 by hbally            #+#    #+#             */
/*   Updated: 2019/01/04 10:45:04 by hbally           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static long double	get_fract_part(long double n)
{
	long long sub;

	sub = (long long)n;
	n -= (long double)sub;
	return (n);
}

static size_t		get_fract_len(long double fract_part)
{
	size_t		i;
	int			digit;

	i = 1;
	while (fract_part > .0f && i < 1000)
	{
		fract_part *= 10;
		digit = (int)(fract_part);
		fract_part -= (long double)digit;
		i++;
	}
	return (i);
}

static char			*fractoa(long double fract_part, char *string)
{
	char		*fract_string;
	char		*concat_result;
	int			digit;
	size_t		len;
	size_t		i;

	len = get_fract_len(fract_part);
	if (!(fract_string = ft_strnew(len)))
		return (NULL);
	fract_string[0] = '.';
	i = 0;
	while (++i < len)
	{
		fract_part *= 10;
		digit = (int)(fract_part);
		fract_string[i] = '0' + digit;
		fract_part -= (long double)digit;
	}
	concat_result = ft_strjoin(string, fract_string);
	free(string);
	free(fract_string);
	return (concat_result);
}

char				*ft_ldtoa(long double n)
{
	unsigned long long	int_part;
	long double			fract_part;
	char				*string;

	if (n < 0)
		n *= -1;
	fract_part = get_fract_part(n);
	int_part = (unsigned long long)(n - fract_part);
	if ((string = ft_ulltoa(int_part)))
	{
		if ((string = fractoa(fract_part, string)))
			return (string);
		else
			free(string);
	}
	return (NULL);
}
