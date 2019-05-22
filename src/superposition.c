#include "../includes/lem_in.h"
#include <stdbool.h>

static bool	paths_collide(t_paths *p1, t_paths *p2)
{
	int i;
	int j;

	i = 0;
	while (p1->path[i])
	{
		j = 0;
		while (p2->path[j])
		{
			if (p1->path[i] == p2->path[j])
				return (true);
			j += 1;
		}
		i += 1;
	}
	return (false);
}

static double ants_in_collision(t_paths *curr, t_paths *head)
{
	double ants;

	ants = 0.0;
	while (head)
	{
		if (head != curr && paths_collide(curr, head) != false)
		{
			ants += head->predicted_ants;
		}
		head = head->next;
	}
	return (ants);
}

static void	delete_childs(t_paths *curr, t_paths *head)
{
	int		counter;
	t_paths	*tmp;

	tmp = head;
	counter = 0;
	while (tmp)
	{
		if (tmp != curr && paths_collide(curr, tmp))
		{
			delete_node(&head, counter);
		}
		tmp = tmp->next;
		counter += 1;
	}
}

t_paths		*delete_superposition(t_paths *head, t_env env, t_graph *g)
{
	t_paths	*tmp;
	double	collide;
	int		counter;

	tmp = head;
	counter = 0;
	collide = 0.0;
	while (tmp)
	{
		collide = ants_in_collision(tmp, head);
		if (collide > 0)
		{
			if (collide >= tmp->predicted_ants)
				delete_node(&head, counter);
			else
				delete_childs(tmp, head);
			tmp = head;
			counter = 0;
		}
		if (env.debug)
		{
			ft_fprintf(2, "path: {g}");
			d_print_path(tmp->path, *g);
			ft_fprintf(2, " {R} Ants in collision: %f\n", collide);
		}

		counter += 1;
		tmp = tmp->next;
	}
	return (head);
}