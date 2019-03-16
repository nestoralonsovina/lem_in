#include "../includes/lem_in.h"
#include "../includes/avl.h"

int parse(t_env *env)
{
	char	*file[10000];
	int 	i;
	int		start;

	start = 0;
	i = 0;
	while (simple_gnl(&env->line) > 0)
	{
		if (ft_strchr(env->line, '-'))
			break ;
		if (env->line[0] != '#')
		{
			if (start == 1)
				env->i_start = env->graph.adj_vert;
			else if (start == 2)
				env->i_end = env->graph.adj_vert;
			env->head = avl_insert(env->head, env->line, env->graph.adj_vert);
			if (env->head == NULL)
				ft_printf("hello boiiiiiiiiiiiiiiiiiis\n");
		}
		else if (env->line[1] == '#')
		{
			if (ft_strequ(&env->line[2], "start"))
				start = 1;
			else if (ft_strequ(&env->line[2], "end"))
				start = 2;
		}
		file[i++] = env->line;
	}
	return (1);
}
