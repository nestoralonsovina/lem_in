#include "includes/lem_in.h"

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
				lem->rooms.array[0] = ft_strndup(line, tmp - line); // an improvement could be to don't reallocate the string, but could lead to leak problems or bigger if.
			else if (!start)
				end = ft_strndup(line, tmp - line);
			else
				insert_dtab(&lem->rooms, ft_strndup(line, tmp - line));
			start = (start == 1 || start == 0) ? -1 : start;
		}
		ft_strdel(&line);
	}
	ft_print_tab(lem->rooms.array);
}


int			main(void)
{
	t_lm	lem;

	init_dtab(&lem.rooms, 2);
	lem.rooms.used = 1;
	lem.ants = -1;
	read_graph(&lem);
}
