#include "../includes/lem_in.h"
#include "../includes/avl.h"



static int	repeated_node(t_graph *g, t_node *n, t_node *end)
{
	int		i;

	if (g->adj_list[0] != NULL)
		i = 0;
	else
		i = 1;
	if (end && (ft_strequ(n->name, end->name) || (n->pos.x == end->pos.x\
			&& n->pos.y == end->pos.y)))
		return (1);
	while (g->adj_list[i])
	{
		if (ft_strequ(g->adj_list[i]->name, n->name)\
				|| (g->adj_list[i]->pos.x == n->pos.x\
					&& g->adj_list[i]->pos.y == n->pos.y))
			return (1);
		i += 1;
	}
	return (0);
}

static int	parse_room(t_env *env, int *start)
{
	char	**tab;
	t_node	*new_node;

	if (ft_strchr(env->line, '-') && !ft_strchr(env->line, ' '))
		return (0);
	if ((tab = ft_strsplit(env->line, ' ')) && ft_tab_len(tab) == 3)
	{
		if (ft_strver(tab[1], ft_isdigit) && ft_strver(tab[2], ft_isdigit)\
				&& tab[0][0] != 'L')
		{
			new_node = create_node(tab[0], ft_atoi(tab[1]), ft_atoi(tab[2]));
			if (!repeated_node(&env->graph, new_node, env->end))
			{
				if (!*start)
					append_node(&env->graph, new_node);
				else if (*start == 1)
					env->graph.adj_list[0] = new_node;
				else if (*start == 2)
					env->end = new_node;
				*start = 0;
				ft_free_tab(tab);
				return (1);
			}
		}
	}
	ft_free_tab(tab);
	return (0);
}

int			read_rooms(t_env *env)
{
	int		start;

	start = 0;
	while (simple_gnl(&env->line) > 0)
	{
		if (env->line[0] != '#' || (env->line[0] == '#' && env->line[1] == '#'))
		{
			if (ft_strequ("##start", env->line))
				start = 1;
			else if (ft_strequ("##end", env->line))
				start = 2;
			else if (!parse_room(env, &start))
				break ;
		}
		ft_strdel(&env->line);
	}
	if (!env->end || !env->graph.adj_list[0])
		return (0);
	append_node(&env->graph, env->end);
	return (1);
}

