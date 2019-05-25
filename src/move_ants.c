#include "../includes/lem_in.h"

t_path	*new_path_node(t_node *r, int len, int ant)
{
	t_path *n;

	n = malloc(sizeof(*n));
	n->room = r;
	n->len = len;
	n->ant = ant;
	return (n);
}

t_path	**create_path(t_graph *g, t_edge **p)
{
	int		i;
	int		len;
	t_path	**path;

	len = plen(p) + 1;
	path = (t_path **)malloc(sizeof(t_path *) * (len + 1));
	path[0] = new_path_node(g->adj_list[g->source.index], len, g->nb_ant);

	i = 1;
	while (i < len)
	{
		path[i] = new_path_node(g->adj_list[p[i - 1]->to], len, 0);
		i += 1;
	}
	path[i] = NULL;
	return (path);
}

/*
 * Function: create_index
 *  returns an array with the index you have to move ants from
 */

int 	*create_index(t_path **path)
{
	int		*a;
	int 	i;
	int 	j;
	int 	len;

	i = 0;
	len = path[0]->len;
	j = len - 2;
	a = malloc(sizeof(int) * (len + 1));
	while (j >= 0)
	{
		if (path[j]->room->ant != 0)
			a[i++] = j;
		j -= 1;
	}
	a[i] = -1;
	return (a);
}

/*
 ** Function: move_ant
 * should make all the necessary movements in a path in each call to the function
 */

void	move_ant(t_path **path, int nb_ant, int last_path)
{
	int 	*index_array;
	int 	current;
	int		i;

	current = 0;
	index_array = create_index(path);
	current = 0;
	while ((i = index_array[current]) != -1)
	{
		if (i == 0)
		{
			path[i + 1]->room->ant = (nb_ant - path[0]->room->ant) + 1;
			path[0]->room->ant -= 1;
		}
		else if (i + 1 == path[i]->len - 1)
		{
			path[i + 1]->room->ant += 1;
			path[i]->room->ant = 0;
		}
		else
		{
			path[i + 1]->room->ant = path[i]->room->ant;
			path[i]->room->ant = 0;
		}
		ft_printf("L%d-%s", path[i + 1]->room->ant, path[i + 1]->room->name);
		if (index_array[current + 1] != -1)
			ft_putchar(' ');
		else if (!last_path)
			ft_putchar(' ');
		current += 1;
	}
	free(index_array);
}

/*
 ** Function: make_movements
 *  function to initialize the path and loop till the end
 */

void		play(t_graph *g, t_paths *head)
{

	t_paths *ptr;
	int		last_path;

	g->adj_list[g->source.index]->ant = g->nb_ant;

	// make a path for each member of the list
	ptr = head;
	while (ptr)
	{
		ptr->move = create_path(g, ptr->path);
		ptr = ptr->next;
	}
	// move the ants
	while (g->adj_list[g->sink.index]->ant != g->nb_ant)
	{
		ptr = head;
		last_path = 0;
		while (ptr)
		{
			if (ptr->next == NULL)
				last_path = 1;
			move_ant(ptr->move, g->nb_ant, last_path);
			ptr = ptr->next;
		}

		ft_putendl(0);
	}
}
