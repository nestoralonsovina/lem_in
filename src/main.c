#include "../includes/lem_in.h"
#include <stdio.h>

void		bfs(t_graph *g, int src, size_t dst);
void		bfs_oreilly(t_graph *g, int src, int nb_ants);
int 		EK(t_env *env, t_graph *g);
int			min_cos_max_flow_with_bellman_ford(t_graph *g);

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
				if (env.debug) {
					d_print_links(&env.graph);
				}
				int flow = EK(&env, &env.graph);
				int algo = min_cos_max_flow_with_bellman_ford(&env.graph);
				ft_printf("max flow: %d\n", flow);
			}
		}
	}
	else
		ft_printf("ERROR with ants\n");
	if (error)
		ft_printf("ERROR\n");
	return (1);
}
