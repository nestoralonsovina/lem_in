/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gb_collector.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 09:15:49 by jallen            #+#    #+#             */
/*   Updated: 2019/06/04 11:26:46 by jallen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GB_COLLECTOR_H
# define GB_COLLECTOR_H

# include <stdlib.h>
# include <string.h>
# include "../libft/includes/libft.h"

typedef	struct			s_lst
{
	void				**arr;
	void				*content;
	size_t				size;
	struct s_lst		*next;
}						t_lst;

t_lst	*g_head;

/*
**	t_lst func
*/

void	g_add(t_lst **head, t_lst *new);
t_lst	*g_new();

/*
**	t_lst 
*/

void	*gb_malloc(void	*content, int size);

#endif
