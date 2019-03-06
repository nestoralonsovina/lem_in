#include "../includes/lem_in.h"

/*
 ** Temporary functions
 ** -------------------
 */

int			ft_strver(char *str, int (f)(int))
{
	while (*str)
	{
		if (f(*str) == 0)
			return (0);
		str += 1;
	}
	return (1);
}

int			add_edge(t_graph *graph, int src, int dst)
{
	if (src == -1 || dst == -1)
		return (0);
	if (graph->adj_list[src]->links == NULL)
		graph->adj_list[src]->links = malloc(sizeof(int) * graph->adj_vert);
	graph->adj_list[src]->links[graph->adj_list[src]->nb_links] = dst;
	graph->adj_list[src]->nb_links += 1;
	return (1);
}

int		get_index(t_node **adj_list, char *name)
{
	size_t i;

	i = 0;
	while (adj_list[i] != NULL)
	{
		if (ft_strequ(adj_list[i]->name, name))
			return (i);
		i += 1;
	}
	return (-1);
}

/*
 ** Function: read_links
 ** --------------------
 ** read the links of form src-dst and add them to the directed graph
 **
 ** env: pointer to general structure
 **
 ** return: success -> 1 and failure -> 0
 */

int			read_links(t_env *env)
{
	char	**tab;

	if (!env->line || !*env->line)
		return (0);
	while (env->line && *env->line)
	{
		if (*env->line != '#')
		{
			tab = ft_strsplit(env->line, '-');
			if (ft_tab_len(tab) != 2)
				return (0);
			if (!add_edge(&env->graph, get_index(env->graph.adj_list, tab[0]),\
						get_index(env->graph.adj_list, tab[1])))
				return (0);
			ft_free_tab(tab);
		}
		ft_strdel(&env->line);
		if (simple_gnl(&env->line) <= 0)
			break ;
	}
	return (1);
}

/*
 ** Function: read_rooms
 ** --------------------
 ** read all the rooms creating a node for each one
 **
 ** env: pointer to general structure
 **
 ** return: success -> 1 and failure -> 0
 */

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
			if (!search_trie(env->root_names, tab[0]))
			{
				insert_trie(env->root_names, tab[0]);
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

/*
 ** Function: read_ants
 ** --------------------
 ** read the number of ants, verifying the input
 **
 ** env: pointer to general structure
 **
 ** return: success -> 1 and failure -> 0
 */

int			read_ants(t_env *env)
{
	if (simple_gnl(&env->line) > 0)
	{
		if (*env->line && ft_strver(env->line, ft_isdigit) && *env->line != '0')
		{
			env->nb_ant = ft_atoi(env->line);
			ft_strdel(&env->line);
			return (1);
		}
		ft_strdel(&env->line);
	}
	return (0);
}
