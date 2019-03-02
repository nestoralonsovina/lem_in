#include "../includes/lem_in.h"

int	main(void)
{
	t_env	env;

	ft_printf("Starting parsing...\n");

	while (simple_gnl(&(env.line)) > 0)
	{
		ft_printf("%s\n", env.line);
		free(env.line);
	}
}
