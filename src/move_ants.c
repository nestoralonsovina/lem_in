#include "../includes/lem_in.h"

/*
 ** Function: create_path
 * 	it should receive a pred and dist, arrays and form a two dimensional array of t_path
 */

static int plen(t_edge **p)
{
	int i;

	i = 0;
	while (p[i] != NULL)
	{
		i++;
	}
	return (i);
}

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

int		check_room(t_path **path, int len)
{
	int		i;
	int		sp;

	i = 1;
	sp = 0;
	while (len > 0)
	{
		if (path[i]->room->ant > 0)
			sp++;
		len--;
	}
	return (sp);
}

void	move_ant(t_path **path, int nb_ant, int last_path, t_paths *head)
{
	int		i;
	int		sp;

	i = head->len - 1;
	sp = 0;
	while (i > 0)
	{
		if (path[i]->room->ant > 0)
		{
			if (i + 1 == head->len)
				path[i + 1]->room->ant += 1;
			else
				path[i + 1]->room->ant = path[i]->room->ant;
			ft_printf("L%d-%s", path[i]->room->ant, path[i + 1]->room->name);
			path[i]->room->ant = 0;
		}
		if (i == 1)
		{
			if (path[1]->room->ant == 0 && path[0]->room->ant > 0 && head->predicted_ants > 0)
			{
				path[1]->room->ant = nb_ant - path[0]->room->ant + 1;
				ft_printf("L%d-%s", path[1]->room->ant, path[1]->room->name);			
				path[0]->room->ant -= 1;
			}
		}
		i--;
	}
}

/*
 ** Function: make_movements
 *  function to initialize the path and loop till the end
 */
static void recalculate_ants(t_paths *head, t_graph *g, int debug, int ants)
{
	t_paths *curr;

	curr = head;
	g->predicted = 0;
	while (curr)
	{
		curr->predicted_ants = compute_ants(head, curr, ants);
		g->predicted += curr->predicted_ants;
		if (debug)
			ft_fprintf(2, "{y}nb_ants = %i{R}\n", curr->predicted_ants);
		curr = curr->next;
	}
}

void		play(t_graph *g, t_paths *head, t_env env)
{

	t_paths *ptr;
	int		last_path;
	int		cnt = 0;
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
		last_path = 1;
		while (ptr)
		{
			move_ant(ptr->move, g->nb_ant, last_path, ptr);
			if (head->predicted_ants > 0)
				head->predicted_ants -= 1;
			g->predicted -= 1;
			ptr = ptr->next;
		}
		cnt++;
		ft_putendl(0);
	}
}
