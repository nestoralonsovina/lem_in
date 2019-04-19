#include "../includes/lem_in.h"

/*
 ** Function: read_links
 ** --------------------
 ** read the links of form src-dst and add them to the directed graph
 **
 ** env: pointer to general structure
 **
 ** return: success -> 1 and failure -> 0
 */

static void		start_links(t_graph *g)
{
	int	i;

	i = 0;
	while (i < g->adj_vert)
	{
		g->adj_list[i]->links = malloc(sizeof(t_edge) * g->adj_vert);
		i += 1;
	}
}

int			read_links(t_env *env)
{
	char	**tab;

	start_links(&env->graph);
	if (!env->line || !*env->line)
		return (0);
	while (env->line && *env->line)
	{
		if (*env->line != '#')
		{
			tab = ft_strsplit(env->line, '-');
			if (ft_tab_len(tab) != 2)
				return (0);
			if (!add_edge(&env->graph, env->rooms.get_index(env->rooms.head, ft_djb2(tab[0])), env->rooms.get_index(env->rooms.head, ft_djb2(tab[1])), 1))
				return (0);
			ft_free_tab(tab);
		}
		ft_strdel(&env->line);
		if (gnl_stdout(&env->line) <= 0)
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

char 	*is_room(char *line)
{
	char	**room;
	char 	*name;

	name = NULL;
	if (!(room = ft_strsplit(line, ' ')))
		return (NULL);
	if (ft_tab_len(room) == 3)
	{
		if (room[0][0] != 'L' && room[0][0] != '#')
		{
			if (ft_strver(room[1], ft_isdigit) &&
					ft_strver(room[2], ft_isdigit))
				name = ft_strdup(room[0]);
		}
	}
	ft_free_tab(room);
	return (name);
}

void	save_room(t_env *env, char *room, int *start)
{
	t_node	*new_node;

	if (*start == 1)
		env->graph.source.index = env->graph.adj_vert;
	else if (*start == 2)
		env->graph.sink.index = env->graph.adj_vert;
	*start = (*start > 0) ? 0 : 0;
	if (env->rooms.insert(&env->rooms, ft_djb2(room), env->graph.adj_vert) == 1)
	{
		if (!(new_node = create_node(room)))
			ft_putendl_fd(ERROR_MALLOC, 2);
		if (new_node)
			append_node(&env->graph, new_node);
	}
	else
	{
		ft_putendl_fd(ERROR_REPEATED_ROOM, 2);
		exit(1);
	}
}

int 	read_rooms(t_env *env)
{
	int 	start = 0;
	char 	*line = NULL;
	char 	*room = NULL;

	while (gnl_stdout(&env->line) && !ft_strchr(env->line, '-'))
	{
		line = env->line;
		if (!(line[0] == '#' && *(line + 1) && line[1] != '#'))
		{
			if (ft_strequ(line, "##start"))
				start = 1;
			else if (ft_strequ(line, "##end"))
				start = 2;
			else if ((room = is_room(line)))
				save_room(env, room, &start);
			else
			{
				ft_fprintf(2, ERROR_INVALID_ROOM);
				return (0);
			}
		}
		ft_strdel(&line);
	}
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
	if (gnl_stdout(&env->line) > 0)
	{
		if (*env->line && ft_strver(env->line, ft_isdigit) && *env->line != '0')
		{
			env->graph.nb_ant = ft_atoi(env->line);
			ft_strdel(&env->line);
			return (1);
		}
		ft_strdel(&env->line);
	}
	return (0);
}
