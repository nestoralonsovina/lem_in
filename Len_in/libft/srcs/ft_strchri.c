/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchri.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbally <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 21:07:45 by hbally            #+#    #+#             */
/*   Updated: 2019/01/18 21:08:15 by hbally           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int			ft_strchri(const char *s, const char c)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	if (s[i] == '\0' && c == '\0')
		return (i);
	else
		return (-1);
}