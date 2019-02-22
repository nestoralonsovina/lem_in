/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalonso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 11:42:30 by nalonso           #+#    #+#             */
/*   Updated: 2019/02/22 11:47:46 by nalonso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void		print_matrix(int **matrix, int rows, int cols)
{
	t_point p;

	p.y = -1;
	while (++p.y < rows)
	{
		p.x = -1;
		while (++p.x < cols)
		{
			if (p.x + 1 != cols)
			{
				if (matrix[p.y][p.x] == 0)
					ft_printf("{r}%-3d{R}", matrix[p.y][p.x]);
				else
					ft_printf("{g}%-3d{R}", matrix[p.y][p.x]);
			}
			else
			{
				if (matrix[p.y][p.x] == 0)
					ft_printf("{r}%d{R}\n", matrix[p.y][p.x]);
				else
					ft_printf("{g}%d{R}\n", matrix[p.y][p.x]);
			}
		}
	}
}
