/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gb_collector.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 09:15:49 by jallen            #+#    #+#             */
/*   Updated: 2019/06/11 20:00:10 by jallen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GB_COLLECTOR_H
# define GB_COLLECTOR_H

# include <stdlib.h>
# include <string.h>
# include "../libft/includes/libft.h"

typedef struct	s_gb
{
	void		**pointers;
	size_t		arr_len;
	size_t		mem_len;
}				t_gb;


/*
 **	t_lst func
 */

void	*gb_malloc(void	*content, int size);


#endif
