#include "../includes/lem_in.h"

t_edge	*spe_add_edge(t_graph *g, int src, int dst)
{
	t_edge	*e;

	e = malloc(sizeof(t_edge));
	e->flow = 0;
	e->from = src;
	e->to = dst;
	e->capacity = 2147483647;
	e->rev = NULL;

	g->adj_list[src]->links[g->adj_list[src]->nb_links++] = e;
	g->adj_list[src]->links[g->adj_list[src]->nb_links] = NULL;
	return (e);
}


void	delete_edge(t_graph *g, int src, int dst)
{
	t_node *curr;

	curr = g->adj_list[src];
	for (int j = 0; j < curr->nb_links; j++)
	{
		if (curr->links[j])
		{
			if (curr->links[j]->to == dst)
			{
				curr->links[j] = NULL;
				break ;
			}
		}
	}

	curr = g->adj_list[dst];
	for (int j = 0; j < curr->nb_links; j++)
	{
		if (curr->links[j])
		{
			if (curr->links[j]->to == src)
			{
				curr->links[j] = NULL;
				break ;
			}
		}
	}

}

void	redo_graph(t_env env, t_graph *g, t_graph *special)
{
	int i;

	init_graph(special, g->adj_vert * 2 + 1);
	i = 0;
	while (i < g->adj_vert)
	{
		if (i == g->source.index || i == g->sink.index)
		{
			if (i == g->source.index)
				special->source.index = special->adj_vert;
			else
				special->sink.index = special->adj_vert;
			g->adj_list[i]->in_node = special->adj_vert;
			g->adj_list[i]->out_node = special->adj_vert;
			t_node *sp = create_node(g->adj_list[i]->name);
			sp->prev_index = i == g->source.index ? g->source.index : g->sink.index;
			append_node(special, sp);
			i += 1;
			continue;
		}
		t_node	*v_in = create_node(g->adj_list[i]->name);
		v_in->prev_index = i;
		v_in->type |= 1; //01

		t_node	*v_out = create_node(g->adj_list[i]->name);
		v_out->prev_index = i;
		v_out->type |= 2; //10
		int curr_index = special->adj_vert; // so curr_index would be the index of v_in and curr_index + 1 would be the one of v_out
		// is have to add an edge from curr_index to curr_index + 1

		t_edge	*un = malloc(sizeof(t_edge));
		un->to = curr_index + 1;
		un->from = curr_index;
		un->flow = 0;
		un->capacity = 1;
		un->rev = NULL; // somehow i have to deal with this shit FIXME

		v_in->links = malloc(sizeof(t_edge *) * (g->adj_vert * 2)); // we shouldn't have more than one edge here
		v_in->links[v_in->nb_links++] = un;
		v_in->links[v_in->nb_links] = NULL;

		g->adj_list[i]->in_node = special->adj_vert;
		g->adj_list[i]->out_node = special->adj_vert + 1;
		append_node(special, v_in);
		append_node(special, v_out);
		i += 1;
	}

	// now I iterate through the nodes again, adding the edged where they should be.
	i = 0;
	while (i < special->adj_vert)
	{
		if ((special->adj_list[i]->type & 1) == 0)
		{
			special->adj_list[i]->links = malloc(sizeof(t_edge *) * special->adj_vert + 1);
			for (int z = 0; z < special->adj_vert; z++)
				special->adj_list[i]->links[z] = NULL;
		}
		++i;
	}

	i = 0;
	// handle start
	while (i < g->adj_list[g->source.index]->nb_links)
	{
		spe_add_edge(special, special->source.index, \
					g->adj_list[g->adj_list[g->source.index]->links[i]->to]->in_node);
		delete_edge(g, g->source.index, g->adj_list[g->source.index]->links[i]->to);
		i += 1;
	}
	i = 0;
	while (i < g->adj_vert)
	{
		t_node *curr = g->adj_list[i];
		if (i == g->source.index || i == g->sink.index)
		{
			i += 1;
			continue;
		}
		for (int j = 0; j < curr->nb_links; j++)
		{
			if (curr->links[j] != NULL)
			{
				t_edge	*e1 = spe_add_edge(special,\
							curr->out_node,\
							g->adj_list[curr->links[j]->to]->in_node);
				t_edge	*e2 = spe_add_edge(special,\
							g->adj_list[curr->links[j]->to]->out_node,\
							curr->in_node);
				e1->rev = e2;
				e2->rev = e1;
				delete_edge(g, i, curr->links[j]->to);
			}
		}
		i += 1;
	}
}