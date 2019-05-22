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

	i = 1;
	while (i < len)
	{
		if (path[i]->room->ant > 0)
			return (1);
		i++;
	}
	return (0);
}

void	move_ant(t_path **path, int nb_ant, int last_path, t_paths *head)
{
	int		i;
	int		move;
	int		len;
	t_path	**test;
	(void)last_path;

	test = path;
	i = head->len - 1;
	len = head->len;
	move = check_room(test, head->len);
	if (move == 0 && (int)head->predicted_ants == 0)
		return ;
	else if (move == 0 && (int)head->predicted_ants > 0)
	{
		if (test[1] == test[head->len])
			test[1]->room->ant += 1;
		else
			test[1]->room->ant = nb_ant - test[0]->room->ant + 1;
		ft_printf("L%d-%s ", test[1]->room->ant, test[1]->room->name);
		test[0]->room->ant -= 1;
	}
	if (move == 1)
	{
		while (i > 0)
		{
			if (test[i]->room->ant > 0)
			{
				if (i + 1 == len)
					test[i + 1]->room->ant += 1;
				else
					test[i + 1]->room->ant = test[i]->room->ant;
				ft_printf("L%d-%s ", test[i]->room->ant, test[i + 1]->room->name);
				test[i]->room->ant = 0;
			}
			if (i == 1)
			{
				if (test[1]->room->ant == 0 && test[0]->room->ant > 0)
				{
					test[1]->room->ant = nb_ant - test[0]->room->ant + 1;
					ft_printf("L%d-%s ", test[1]->room->ant, test[1]->room->name);			
					test[0]->room->ant -= 1;
				}
			}
			i--;
		}
	}
}

/*
 ** Function: make_movements
 *  function to initialize the path and loop till the end
 */

void		play(t_graph *g, t_paths *head, t_env env)
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
			move_ant(ptr->move, g->nb_ant, last_path, head);
			if (head->predicted_ants > 0)
				head->predicted_ants -= 1;
			g->predicted -= 1;
			ptr = ptr->next;
		}
		ft_putendl(0);
	}
}
