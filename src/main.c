#include "../includes/lem_in.h"
#include <stdio.h>

void		bfs(t_graph *g, int src, size_t dst);
void		bfs_oreilly(t_graph *g, int src, int nb_ants);
int 		edmonds_karp(t_env *env, t_graph *g, int src, int dst);

void	d_print_links(t_graph *g)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (g->adj_list[i] != NULL)
	{
		ft_printf("%s - links: %d\n", g->adj_list[i]->name, g->adj_list[i]->nb_links);
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

 void init_env(t_env *env)
{
	init_graph(&env->graph, 1024);
	env->graph.adj_list[0] = NULL;
	env->graph.adj_list[1] = NULL;
	env->end = NULL;
	env->graph.adj_vert = 1;
}

int			main(int ac, char **av)
{
	t_env	env;
	int		error;

	init_env(&env);
	error = 1;
	if (read_ants(&env))
	{
		if (read_rooms(&env))
		{
			ft_printf("Reading links\n");
			if (read_links(&env))
			{

				error = 0;
				ft_printf("Entering Edmonds\n");
				int ret = edmonds_karp(&env, &env.graph, 0, env.graph.adj_vert - 1);
				ft_printf("Max flow: %d\n", ret);
			}
			else
				ft_printf("ERROR with links\n");
		}
		else
			ft_printf("ERROR with rooms\n");
	}
	else
		ft_printf("ERROR with ants\n");
	//free_graph(&env.graph);
	if (ac == 2 && ft_strequ(av[1], "-d"))
	{
		d_print_links(&env.graph);
	}
	if (error)
		ft_printf("ERROR\n");
	return (1);
}
