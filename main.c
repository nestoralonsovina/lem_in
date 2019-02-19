# include "libftprintf/includes/ft_printf.h"

typedef struct	s_tab
{
	char			**tab;
	size_t			size;
	unsigned int	curr_i;
}				t_tab;

typedef struct	s_lm
{
	t_tab		rooms;
	int			**table;
	int			ants;
}				t_lm;

static t_tab		reallocate_tab(t_tab tb, int size)
{
	char	**tmp;
	size_t	i;

	tmp = (char **)malloc(sizeof(char *) * size);
	i = 0;
	while(i < size)
	{
		if (tb.tab[i])
			tmp[i] = tb.tab[i];
		else
			tmp[i] = NULL;
		i += 1;
	}
	tmp[i] = NULL;
	tb.size = size;
	return (tb);
}

static t_tab		add_tab(t_tab tb, char *item, int index)
{
	char	*tmp;

	if (index > tb.size + 2)
	{
		tb = reallocate_tab(tb, index + 2);
		tb.tab[tb.curr_i + 1] = item;
	}
	else if (tb.tab[tb.curr_i + 1] == NULL)
		tb.tab[tb.curr_i + 1] = item;
	else
	{
		//if (index == -1)
		//tb = append_start(i
	}

}

static void			init_lem_in(t_lm *lem_in)
{
	lem_in->rooms.tab = (char **)malloc(sizeof(char *) * 69);
	lem_in->rooms.size = 69;
	lem_in->rooms.curr_i = 0;
	while (lem_in->rooms.curr_i < lem_in->rooms.size)
		lem_in->rooms.tab[(lem_in->rooms).curr_i++] = NULL;
	lem_in->rooms.curr_i = 1;
	lem_in->ants = -1;
}



int		main(void)
{
	t_lm	lem_in;
	int		ret;
	int		start;
	char	*line;
	char	*end;
	char	*tmp;

	tmp = NULL;
	start = -1;
	ret = 0;
	init_lem_in(&lem_in);
	while ((ret = get_next_line(0, &line)) > 0)
	{
		if (!*line)
			break;
		int		index = lem_in.rooms.curr_i;
		if (line[0] == '#' && ft_strequ("##start", line))
			start = 1;
		else if (line[0] == '#' && ft_strequ("##end", line))
			start = 0;
		if (line[0] != '#' && lem_in.ants == -1)
			lem_in.ants = ft_atoi(line);
		if (line[0] != '#' && !ft_strchr(line, '-')) // FIXME:  names can have - in his name?
		{
			tmp = ft_strchr(line, ' ');
			if (!tmp)
				ft_printf("error bitch\n");
			if (start == 1)
			{
				lem_in.rooms.tab[0] = ft_strsub(line, 0, tmp - line);
				start = -1;
			}
			else if (start == 0)
			{
				start = -1;
				end = ft_strsub(line, 0, tmp - line);
			}
			else
			{
				lem_in.rooms.tab[index] = ft_strsub(line, 0, tmp - line);
				lem_in.rooms.curr_i += 1;
			}
		}
		if (line[0] != '#' && ft_strchr(line, '-'))
		{
			lem_in.rooms.tab[index] = end;
		}
		ft_strdel(&line);
	}
	ft_print_tab(lem_in.rooms.tab);
	return (0);
}
