/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dtoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbally <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/22 18:20:34 by hbally            #+#    #+#             */
/*   Updated: 2018/12/31 16:08:26 by hbally           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

/*
** This is a partial implementation of original dtoa (does not support the
** full range of double values)
**
** /!\/!\/!\/!\/!\
** If value is negative, '-' will not be printed
*/

static double	get_fract_part(double n)
{
	long long sub;

	sub = (long long)n;
	n -= (double)sub;
	return (n);
}

static size_t	get_fract_len(double fract_part)
{
	size_t		i;
	int			digit;

	i = 1;
	while (fract_part > .0f && i < 1000)
	{
		fract_part *= 10;
		digit = (int)(fract_part);
		fract_part -= (double)digit;
		i++;
	}
	return (i);
}

static char		*fractoa(double fract_part, char *string)
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
		fract_part -= (double)digit;
	}
	concat_result = ft_strjoin(string, fract_string);
	free(string);
	free(fract_string);
	return (concat_result);
}

char			*ft_dtoa(double n)
{
	unsigned long long	int_part;
	double				fract_part;
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
