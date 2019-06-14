#include "../includes/lem_in.h"

void	push_room(t_path **path, t_node *r)
{
	int	i;

	i = 0;
	while (path[i] != NULL)
	{
		if (path[i]->room == r)
			return ;
		i += 1;
	}
	t_path *new = malloc(sizeof(t_path));
	new->room = r;
	path[i++] = new;
	path[i] = NULL;
}

void	set_plen(t_path **path)
{
	int	len;
	int	i;

	len = 0;
	while (path[len])
		++len;
	i = 0;
	while (i < len)
	{
		path[i]->len = len;
		path[i]->ant = 0;
		i += 1;
	}
}

void	transform_paths(t_env env, t_graph *sp, t_paths **head_ref)
{
	t_paths	*prev;
	t_path	**tmp;
	t_path	**good;

	prev = *head_ref;
	while (prev != NULL)
	{
		tmp = create_path(sp, prev->path);
		good = malloc(sizeof(t_path *) * sp->adj_vert);
		good[0] = NULL;
		for (int i = 0; i < tmp[0]->len; i++)
		{
			push_room(good, env.graph.adj_list[tmp[i]->room->prev_index]);
		}
		set_plen(good);
		prev->move = good;
		prev->len = good[0]->len - 1;
		prev = prev->next;
	}
}

