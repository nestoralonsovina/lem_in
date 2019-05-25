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

static int	count_movements(t_paths *curr)
{
	int counter;
	int	i;

	i = 1;
	counter = 0;
	if (curr->len > 2)
	{
		while (i < curr->len)
		{
			if (curr->move[i]->room->ant > 0)
			{
				counter += 1;
			}
			i += 1;
		}
	}
	return (curr->predicted_ants > 0 ? counter + 1 : counter);
}
int		check_next(t_path **path, int len, int predicted)
{
	if (predicted > 0)
		return (1);
	while (len > 0)
	{
		if (path[len]->room->ant > 0)
			return (1);
		len--;
	}
	return (0);
}

int		next_path(t_path **path, int len, int predicted)
{
	int	i;

	i = 0;
	if (predicted > 0)
		return (1);
	while (i < len)
	{
		if (path[i]->room->ant > 0)
			return (1);
		i++;
	}
	return (0);
}
void	move_ant(t_path **path, int nb_ant, int *move, t_paths *head)
{
	int		i;

	i = head->len - 1;
	if (head->len == 1 && path[0]->room->ant > 0 && (int)head->predicted_ants > 0)
	{
		path[1]->room->ant += 1;
		ft_printf("L%d-%s", nb_ant - path[0]->room->ant + 1, path[1]->room->name);
		path[0]->room->ant -= 1;
	}
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
			if (check_next(path, i, (int)head->predicted_ants) == 1)
				ft_putchar(' ');
			*move = 1;
		}
		if (i == 1 && path[1]->room->ant == 0 && path[0]->room->ant > 0 && (int)head->predicted_ants > 0)
		{
			path[1]->room->ant = nb_ant - path[0]->room->ant + 1;
			ft_printf("L%d-%s", path[1]->room->ant, path[1]->room->name);			
			path[0]->room->ant -= 1;
			*move = 1;
		}
		i--;
	}
}

/*
 ** Function: make_movements
 *  function to initialize the path and loop till the end
 */
void		play(t_graph *g, t_paths *head, t_env env)
{

	t_paths *ptr;
	int		cnt;
	int		sp;
	int		move;

	g->adj_list[g->source.index]->ant = g->nb_ant;
	// make a path for each member of the list
	ptr = head;
	while (ptr)
	{
		ptr->move = create_path(g, ptr->path);
		ptr = ptr->next;
	}
	cnt = 0;
	while (head->move[head->len]->room->ant != g->nb_ant)
	{
		ptr = head;
		sp = 0;
		while (ptr)
		{
			move = 0;
			move_ant(ptr->move, g->nb_ant, &move, ptr);
			if (ptr->predicted_ants > 0)
				ptr->predicted_ants -= 1;
			sp++;
			ptr = ptr->next;
			if (ptr)
				if (next_path(ptr->move, ptr->len, (int)ptr->predicted_ants) == 1 && sp >= 1
						&& head->move[head->len]->room->ant != g->nb_ant && move == 1)
					ft_putchar(' ');
		}
		ft_putendl(0);
		cnt++;
	}
	ft_fprintf(2, "{y}lines = %i{R}\n", cnt);
}
