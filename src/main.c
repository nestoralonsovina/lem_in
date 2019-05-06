#include "../includes/lem_in.h"
#include <stdio.h>

void		algo(t_env env, t_graph *g);

void init_env(t_env *env)
{
	init_graph(&env->graph, 1024);
	env->rooms = avl_init();
	env->coords = avl_init();
	env->debug = 0;
}

int			main(int ac, char **av)
{
	t_env	env;
	int		error;

	init_env(&env);
	error = 1;
	if (ac == 2 && ft_strequ(av[1], "-d"))
	{
		env.debug = 1;
	}

	if (read_ants(&env))
	{
		if (read_rooms(&env))
		{
			if (read_links(&env))
			{
				error = 0;
				algo(env, &env.graph);
		    }
		}
	}
	else
		ft_printf("ERROR with ants\n");
	if (error)
		ft_printf("ERROR\n");
	free_graph(&env.graph);
	env.rooms.free(env.rooms.head);
	while (1);
	return (1);
}
