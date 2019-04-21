#include "lem_in.h"

static int compute_time(int ants, int mf, int mc) {
	return ((ants / mf) + mc);
}

t_paths *new_path(t_edge **p, int max_flow, int min_cost, int nb_ant)
{
	t_paths		*ptr;

	ptr = (t_paths *)malloc(sizeof(t_paths));
	if (ptr != NULL)
	{
		ptr->path = p;
		ptr->mf = max_flow;
		ptr->mc = min_cost;
		ptr->time = compute_time(nb_ant, max_flow, min_cost);
		ptr->next = NULL;
	}
	return (ptr);
}

void	append_path(t_paths **head, t_paths *new_path)
{
	t_paths *ptr;

	if (new_path)
	{
		if (*head == NULL)
		{
			*head = new_path;
		} else {
			ptr = *head;
			while (ptr->next)
				ptr = ptr->next;
			ptr->next= new_path;	
		}
	}
}

int		count_paths(t_paths *head)
{
	if (!head)
	{
		return (0);
	}
	return 1 + count_paths(head->next);
}

t_edge *intersects(t_paths *known_paths, t_edge *p)
{
	t_paths	*cur;

	cur = known_paths;
	while (cur)
	{
		t_edge **ptr = cur->path;
		ft_fprintf(2, "{y} address: %p {R}\n", ptr);
		while (*ptr != NULL)
		{
			ft_fprintf(2, "{y} address: %p {R}\n", *ptr);
			if ((*ptr)->rev == p) {
				ft_fprintf(2, "{r}Two paths have collided{R}");
				return (p);
			}
			ptr += 1;
		}
		cur = cur->next;
	}

	return (NULL);
}
