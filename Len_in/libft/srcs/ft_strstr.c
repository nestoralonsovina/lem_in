/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbally <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 14:27:41 by hbally            #+#    #+#             */
/*   Updated: 2019/01/26 13:55:22 by hbally           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	unsigned int	i;
	size_t			len_haystack;
	size_t			len_needle;

	i = 0;
	if (!haystack || !needle)
		return (NULL);
	if (!needle[i] && !haystack[i])
		return ((char*)haystack);
	len_needle = ft_strlen(needle);
	len_haystack = ft_strlen(haystack);
	while (haystack[i] && len_needle <= (len_haystack - i))
	{
		if (ft_strncmp(&haystack[i], needle, len_needle) == 0)
			return ((char*)&haystack[i]);
		i++;
	}
	return (NULL);
}
