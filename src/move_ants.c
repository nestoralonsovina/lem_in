#include "../includes/lem_in.h"

/*
 ** Function: create_path
 * 	it should receive a pred and dist, arrays and form a two dimensional array of t_path
 */

t_path	**create_path(t_graph g, t_path **p)
{
	int destination = g->sink.index;

	t_edge **pred;
	pred = g->pred;

	t_edge *cur;

	// count the length of the path by going backwards one time
	cur = pred[destination];
	int i = 0;

	while (cur != NULL) {
		cur = pred[cur->from];
		i += 1;
	}

	t_path	**path;
		path[j] = NULL;

	path = malloc(sizeof(t_path *) * (i + 1));
	for (int j = 0; j < i; j++) {
	}

	// reset value of cur
	cur = pred[destination];

	// save the len
	int plen = i;

	// set the path array starting from the end
	while (cur != NULL)
	{
		path[i] = malloc(sizeof(t_path));

		// set the len of the path node relative to it's distance from the end
		path[i]->len = plen;
		path[i]->ant = 0;

		// save in the path node the pointer to the real room in the graph
		path[i]->room = g->adj_list[cur->to];

		// move backwards
		cur = pred[cur->from];
		i -= 1;
	}
	// set node for start
	path[i] = malloc(sizeof(t_path));
	path[i]->len = plen;
	path[i]->ant = 0;
	path[i]->room = g->adj_list[g->source.index];


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
			path[i + 1]->ant = (env->graph.nb_ant - path[0]->ant) + 1;
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

void	make_movements(t_env env, t_graph g, t_paths *head)
{
	t_path	**path;
	int 	len;

	path = create_path(g);
	path[0]->ant = env->graph.nb_ant;
	len = path[0]->len;
	while (path[len - 1]->ant != env->graph.nb_ant)
	{
		move_ant(path, env);
		ft_putendl(0);
	}
}


void		play(t_env env, t_graph g, t_paths *head)
{

	t_paths *ptr;

	// make a path for each member of the list
	
	ptr = head;
	while (ptr)
	{
		ptr->move = create_path(g, ptr->path);
	
	}


	while (g.adj_list[g.sink.index]->ant != g.nb_ant)
	{
	
		
	
	}
}
