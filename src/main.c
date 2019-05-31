/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalonso <nalonso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 13:48:42 by jallen            #+#    #+#             */
/*   Updated: 2019/05/31 16:50:16 by jallen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"
#include <stdio.h>

static void		init_flag(t_env *env, char *av)
{
	int	i;

	i = 1;
	if (av[0] != '-' || ft_strlen(av) == 1)
	{
		ft_fprintf(2, "Usage : lem_in -[dipn]\n");
		exit(0);
	}
	if (av[0] == '-')
		while (av[i])
		{
			if (ft_strchr("dipn", av[i]) == NULL)
			{
				ft_fprintf(2, "Illegal option %c\nusage : -[dipn]\n", av[i]);
				exit(0);
			}
			if (av[i] == 'd')
				env->debug |= D;
			else if (av[i] == 'i')
				env->debug |= I;
			else if (av[i] == 'n')
				env->debug |= NM;
			i++;
		}
}

static void		init_env(t_env *env, int ac, char *av)
{
	init_graph(&env->graph, 1024);
	env->rooms = avl_init();
	env->coords = avl_init();
	env->graph.sink.index = -1;
	env->graph.source.index = -1;
	if (ac == 2)
		init_flag(env, av);
}

int				main(int ac, char **av)
{
	t_env	env;
	int		error;

	init_env(&env, ac, av[1]);
	error = 1;
	if (read_ants(&env))
	{
		if (read_rooms(&env))
		{
			if (env.graph.source.index == -1 || env.graph.sink.index == -1)
				error = 1;
			else if (read_links(&env))
			{
				error = 0;
				algo(env, &env.graph);
			}
		}
	}
	if (error)
		ft_printf("ERROR\n");
	free_graph(&env.graph);
	env.rooms.free(env.rooms.head);
	env.coords.free(env.coords.head);
	free(env.line);
	return (1);
}
