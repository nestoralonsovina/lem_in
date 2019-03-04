#include "../includes/lem_in.h"
/*
static void	d_print_rooms(t_graph *graph)
{
	size_t i;

	i = 0;
	while (graph->adj_list[i])
	{
		ft_printf("room: %d, name: %s, xy: (%d, %d)\n", i,\
				graph->adj_list[i]->name,\
				graph->adj_list[i]->pos.x,\
				graph->adj_list[i]->pos.y);
		i += 1;
	}
}
*/
static void	d_print_links(t_graph *g)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (g->adj_list[i] != NULL)
	{
		ft_printf("%s\n", g->adj_list[i]->name);
		while (j < g->adj_list[i]->nb_links)
		{
			ft_printf("{g}%5s{R} %s\n", "-->",\
					g->adj_list[g->adj_list[i]->links[j]]->name);
			j += 1;
		}
		j = 0;
		i += 1;
		ft_printf("\n");
	}
}

static void init_env(t_env *env)
{
	env->debug = 0;
	init_graph(&env->graph, 1024);
	env->graph.adj_list[0] = NULL;
	env->graph.adj_list[1] = NULL;
	env->graph.adj_vert = 1;
}

int			main(int ac, char **av)
{
	t_env	env;
	int		error;

	init_env(&env);
	if (ac == 2 && ft_strequ(av[1], "-d"))
		env.debug = 1;
	error = 1;
	if (read_ants(&env))
	{
		if (read_rooms(&env))
		{
			if (read_links(&env))
			{
				if (env.debug)
				{
					d_print_links(&env.graph);
					//d_print_rooms(&env.graph);
				}
				error = 0;
			}
		}
	}
	free_graph(&env.graph);
	if (error)
		ft_printf("ERROR\n");
	return (1);
}
