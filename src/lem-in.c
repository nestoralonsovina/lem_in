#include "../includes/lem_in.h"

int			**create_matrix(int rows, int cols)
{
	int		**new;
	int		i;
	int		j;

	new = (int **)malloc(sizeof(int *) * rows);
	i = 0;
	j = 0;
	while (i < rows)
	{
		new[i] = (int *)malloc(sizeof(int) * cols);
		while (j < cols)
		{
			new[i][j] = 0;
			j += 1;
		}
		j = 0;
		i += 1;
	}
	return (new);
}

int			index_of(t_dtab a, char *s)
{
	char	**ptr;

	ptr = a.array;
	while (a.used--)
	{
		if (ft_strequ(*(a.array), s))
			return (a.array - ptr);
		a.array += 1;
	}
	return (-1);
}

void		read_graph(t_lm *lem)
{
	char	*line;
	char	*end;
	char	*tmp;
	int		ret;
	int		start;

	start = -1;
	while ((ret = get_next_line(0, &line)) > 0)
	{
		if (!line || !*line)
			continue ;
		if (ft_strequ("##start", line))
			start = 1;
		else if (ft_strequ("##end", line))
			start = 0;
		else if (line[0] == '#') // exeption if room starts with L
		{
			ft_strdel(&line);
			continue ;
		}
		else if (lem->ants == -1) // input ants < 0 at the end print error
			lem->ants = ft_atoi(line);
		else if (!ft_strchr(line, '-')) // should do a function to check correct formatting and everything
		{								// name could contain - hehe
			tmp = ft_strchr(line, ' ');
			if (!tmp)
				continue ; // migth produce leak when line is blank, but is the way to skip it
			if (start == 1)
				index_dtab(&lem->rooms, ft_strndup(line, tmp - line), 0);
			else if (!start)
				end = ft_strndup(line, tmp - line);
			else
				insert_dtab(&lem->rooms, ft_strndup(line, tmp - line));
			start = (start == 1 || start == 0) ? -1 : start;
		}
		else if ((tmp = ft_strchr(line, '-')))
		{
			if (lem->graph == NULL)
			{
				insert_dtab(&lem->rooms, end);
				lem->graph = create_matrix(lem->rooms.used, lem->rooms.used);

			}
			*tmp = '\0';
			int v1 = index_of(lem->rooms, line);
			int v2 = index_of(lem->rooms, tmp + 1);

			lem->graph[v1][v2] = 1;
			lem->graph[v2][v1] = 1;
		}
		ft_strdel(&line);
	}
	//ft_print_tab(lem->rooms.array);
	//ft_printf("rows: %d, cols: %d\n", lem->rooms.used, lem->rooms.used);
	print_matrix(lem->graph, lem->rooms.used, lem->rooms.used);
}


int			main(void)
{
	t_lm	lem;

	init_dtab(&lem.rooms, 2048);
	lem.ants = -1;
	lem.graph = NULL;
	read_graph_improved(&lem);
}
