#include "../includes/lem_in.h"

/*
** Function: create_path
 * 	it should receive a pred and dist, arrays and form a two dimensional array of t_path
*/

t_path	**create_path(t_graph *g)
{
	t_path	**path;
	int 	current;
	int 	i;

	current = g->adj_vert - 1;
	i = g->dist[current];
	path = malloc(sizeof(t_path *) * (i + 1));
	while (current != -1)
	{
		path[i] = malloc(sizeof(t_path));
		path[i]->len = g->dist[g->adj_vert - 1] + 1;
		path[i]->ant = 0;
		path[i]->room = g->adj_list[current];
		i -= 1;
		current = g->pred[current];
	}
	return (path);
}

/*
** Function: print_path
** print a path of type t_path **
*/

void	print_path(t_path **path)
{
	int len;
	int i;

	i = 0;
	len = path[i]->len;
	while (i < len)
	{
		if (i + 1 < len)
			ft_printf("%s --> ", path[i]->room->name);
		else
			ft_printf("%s\n", path[i]->room->name);
		i += 1;
	}
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
	len = path[i]->len;
	j = len - 2;
	a = malloc(sizeof(int) * (len + 1));
	while (j >= 0)
	{
		if (path[j]->ant != 0)
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

void	print_array(int *a)
{
	while (*a != -1)
	{
		ft_printf("{r}%d {R}", *a);
		a++;
	}
	ft_putendl(0);
}

void	print_ants(t_path **p)
{
	int i, len;

	i = 0;
	len = p[i]->len;
	while (i < len)
	{
		ft_fprintf(2, "{r}%d --> {R}", p[i]->ant);
		i += 1;
	}
	ft_putendl(0);
}

void	move_ant(t_path **path, t_env *env)
{
	int 	*index_array;
	int 	current;
	int		i;

	current = 0;
	index_array = create_index(path);
	while ((i = index_array[current]) != -1)
	{
		if (i == 0)
		{
			path[i + 1]->ant = (env->nb_ant - path[0]->ant) + 1;
			path[0]->ant -= 1;
		}
		else if (i + 1 == path[i]->len - 1)
		{
			path[i + 1]->ant += 1;
			path[i]->ant = 0;
		}
		else
		{
			path[i + 1]->ant = path[i]->ant;
			path[i]->ant = 0;
		}
		ft_printf("L%d-%s", path[i + 1]->ant, path[i + 1]->room->name);
		ft_putchar(' ');
		current += 1;
	}
	free(index_array);
}

/*
** Function: make_movements
 *  function to initialize the path and loop till the end
 */

void	make_movements(t_graph *g, t_env *env)
{
	t_path	**path;
	int 	len;

	path = create_path(g);
	path[0]->ant = env->nb_ant;
	len = path[0]->len;
	while (path[len - 1]->ant != env->nb_ant)
	{
		move_ant(path, env);
		ft_putendl(0);
	}
}
