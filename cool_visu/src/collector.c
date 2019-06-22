/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collector.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbally <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 15:44:03 by hbally            #+#    #+#             */
/*   Updated: 2019/03/20 14:14:51 by hbally           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "lem_in.h"

void			collector(t_wrap *wrap, uint8_t flag)
{
	if (flag == KO)
	{
		ft_printf("ERROR\n");
		ft_free_wrap(wrap);
		exit(EXIT_FAILURE);
	}
	if (flag == DONE)
		output_wrapper(wrap, &(wrap->graph));
	ft_free_wrap(wrap);
	if (flag == DONE)
		exit(EXIT_SUCCESS);
}
