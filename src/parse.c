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
		return (1);
	if ((tab = ft_strsplit(env->line, ' ')) && ft_tab_len(tab) == 3)
	{
		if (ft_strver(tab[1], ft_isdigit) && ft_strver(tab[2], ft_isdigit)\
				&& tab[0][0] != 'L')
		{
			new_node = create_node(tab[0], ft_atoi(tab[1]), ft_atoi(tab[2]));
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
	ft_free_tab(tab);
	ft_printf("ERROR: Invalid room input\n");
	return (0);
}

int			read_rooms(t_env *env)
{
	int		start;

	start = 0;
	init_graph(&env->graph, 1024);
	env->end = NULL;
	env->graph.adj_list[0] = NULL;
	env->graph.adj_vert = 1;
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
	char	*line;

	if (simple_gnl(&line) > 0)
	{
		if (line[0] != '#' && *line && ft_strver(line, ft_isdigit))
		{
			env->nb_ant = ft_atoi(line);
			ft_strdel(&line);
			return (1);
		}
		ft_strdel(&line);
	}
	ft_fprintf(2, "ERROR: Unable to read number of ants\n");
	return (0);
}
