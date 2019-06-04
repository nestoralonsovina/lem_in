/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalonso <nalonso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 17:46:54 by nalonso           #+#    #+#             */
/*   Updated: 2019/06/02 16:02:32 by jallen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"





void	algo(t_env env, t_graph *g)
{
	t_paths	*head;

	head = NULL;
	if (head == NULL && ft_fprintf(2, "ERROR\n"))
		exit(EXIT_FAILURE);
	print_file(env.debug);
	g->nb_p = count_paths(head);
	play(g, head, env.debug);
	free_paths(head);
}
