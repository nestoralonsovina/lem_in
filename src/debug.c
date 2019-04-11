#include "../includes/lem_in.h"

void	print_edge(t_edge *e) {
	ft_printf("to: %d, from: %d, flow: %d, cap: %d\n", e->to, e->from, e->flow, e->cap);
}

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
					g->adj_list[g->adj_list[i]->links[j]->to]->name);
			j += 1;
		}
		j = 0;
		i += 1;
		ft_printf("\n");
	}
}
