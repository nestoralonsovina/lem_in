#include "../includes/lem_in.h"

/*
** @assign_flow:
** @param -
** 	line to be analized
** @return
** 		0	if command is ##end
**		1	if command is ##start
** 		-1	if not start of end
*/

int			assign_flow(char **line)
{
	if (ft_strncmp(*line, "##", 2) != 0)
	{
		ft_strdel(line);
		return (-1);
	}
	if (ft_strequ(*(line + 2), "start"))
	{
		ft_strdel(line);
		return (1);
	}
	else if (ft_strequ(*(line + 2), "end"))
	{
		ft_strdel(line);
		return (0);
	}
	return (-1);
}

int			handle_format(t_lm *lem, char *line, int *start)
{
	char	*tmp;

	(void)lem;
	if ((tmp = ft_strchr(line, ' ')))
	{
		if (*start == -2)
		{
			ft_printf("ERROR");
			exit(EXIT_FAILURE);
		}
		return (1);
	}
	else if ((tmp = ft_strchr(line, '-')))
	{

	}
	return (0);
}

void		read_graph_improved(t_lm *lem)
{
	int		ret;
	int		start;
	char	*line;

	while ((ret = get_next_line(0, &line)) > 0)
	{
		ft_putendl(line);
		start = (*line == '#') ? assign_flow(&line) : -1;
		if (!line)
			continue ;
		handle_format(lem, line, &start);
		ft_strdel(&line);
	}
}
