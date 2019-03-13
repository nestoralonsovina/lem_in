#include "../includes/lem_in.h"
#include <limits.h>

typedef struct	s_path
{
	int 			nb_ant;
	t_node			*node;
	struct s_path	*next;
	struct s_path	*prev;
}				t_path;


t_path	*create_path(t_graph *g)
{
	t_path	*root;
	t_path	*tmp;
	int		i;

	i = g->adj_vert - 1;
	root = NULL;
	while (i != -1)
	{
		tmp = malloc(sizeof(t_path));
		tmp->node = g->adj_list[i];
		tmp->nb_ant = 0;
		tmp->next = root;
		root = tmp;
		i = g->pred[i];
	}
	return (root);
}

t_path	*go_empty(t_path *p)
{
	while (p)
	{
		// we are at the end
		if (!p->next)
			break;
		if (p->nb_ant == 0)
			break;
		p = p->next;
	}
	return (p);
}

t_path	*go_last(t_path *p)
{
	while (p->next)
		p = p->next;
	return (p);
}

t_path	*path_get_index(t_path *p, int index)
{
	int 	i;

	i = 1;
	while (i < index)
	{
		p = p->next;
		i += 1;
	}
	return (p);
}

int 	get_steps(t_path *p)
{
	int	pasos;
	t_path	*end;
	t_path	*current;

	pasos = 1;
	end = go_last(p);
	current = p->next;
	while (current != end)
	{
		if (current->nb_ant != 0)
			pasos += 1;
		current = current->next;
	}
	return (pasos);
}

int 	move_ant(t_path *p, t_env *env)
{
	int	pasos;
	t_path	*end;
	t_path	*current;

	pasos = get_steps(p);

	end = go_last(p);
	p->nb_ant = env->nb_ant;
	ft_printf("pasos: %d\n", pasos);
	while (pasos > 0)
	{
		current = path_get_index(p, pasos);
		if (current == p)
		{
			current->next->nb_ant = env->nb_ant - current->nb_ant + 1;
			ft_printf("L%d%s-%s", current->next->nb_ant, current->node->name, current->next->node->name);
			current->nb_ant -= 1;
		}
		else if (current->next == end)
		{
			current->next->nb_ant += 1;
			current->nb_ant = 0;
		}
		else
		{
			current->next->nb_ant = current->nb_ant;
			current->nb_ant = 0;

		}
		pasos -= 1;
	}
	ft_putendl(0);
	return 0;
}

void	print_path(t_graph *g)
{
	t_path *p;

	p = create_path(g);
	while (p)
	{
		if (p->next)
			ft_printf("%s --> ", p->node->name);
		else
			ft_printf("%s", p->node->name);
		p = p->next;
	}
	ft_putendl(0);
}

void	print_matrix(t_graph *g)
{
	for (int v = 0; v < g->adj_vert; v++) {
		for (int w = 0; w < g->adj_vert; w++) {
			ft_printf("%3d", g->flow[v][w]);
		}
		ft_printf("\n");
	}
}

void	create_matrix(t_graph *g, int n)
{
	int 	i;
	int 	j;

	i = 0;
	g->flow = malloc(sizeof(int *) * n);
	while (i < n)
	{
		g->flow[i] = malloc(sizeof(int) * n);
		j = 0;
		while (j < n)
		{
			g->flow[i][j] = 0;
			j += 1;
		}
		i += 1;
	}
}

int 	aumenting_path(t_graph *g, int src, int dst)
{
	t_queue	*q;
	int 	i;

	// create circular queue
	q = create_queue(g->adj_vert);
	enqueue(q, src);

	// restart visited and pred arrays
	i = 0;
	while (i < g->adj_vert)
	{
		g->pred[i] = -1;
		g->visited[i] = 0;
		i += 1;
	}

	// initialize previous and visited to start loop
	g->pred[src] = -1;
	g->visited[src] = 1;

	while (q->size != 0)
	{
		int u = front(q);
		int n = g->adj_list[u]->nb_links;

		for (int ngb = 0; ngb < n; ngb++)
		{
			int v = g->adj_list[u]->links[ngb];
			if (v == u || g->visited[v] != 0)
				continue;
			if (g->flow[u][v] < 1)
			{
				enqueue(q, v);
				g->visited[v] = 1;
				g->pred[v] = u;
			}
		}
		dequeue(q);
	}
	return (g->visited[dst] != 0);
}

int 	process_path(t_graph *g, int dst)
{
	int v = dst;

	int increment = 1;

	while (g->pred[v] != -1)
	{
		g->flow[g->pred[v]][v] += increment;
		g->flow[v][g->pred[v]] -= increment;

		v = g->pred[v];
	}

	return (increment);
}

int		edmonds_karp(t_env *env, t_graph *g, int src, int dst)
{
	int max_flow;
	int ret;

	create_matrix(g, g->adj_vert);
	g->pred = malloc(sizeof(int) * g->adj_vert);
	g->visited = malloc(sizeof(int) * g->adj_vert);
	max_flow = 0;
	ret = aumenting_path(g, src, dst);
	/*
	while (ret == 1)
	{
		max_flow += process_path(g, dst);
		print_path(g);
		ret = aumenting_path(g, src, dst);
	}*/
	print_path(g);
	move_ant(create_path(g), env);
	move_ant(create_path(g), env);
	return (max_flow);
}
