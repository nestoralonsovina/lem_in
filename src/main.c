#include "../includes/lem_in.h"

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

int			main(void)
{
	t_env	env;

	ft_printf("Starting parsing...\n");
	if (read_ants(&env))
	{
		if (read_rooms(&env))
		{
			d_print_rooms(&env.graph);
			return (0);
		}
	}
	ft_printf("Finished parsing... \n");
}
