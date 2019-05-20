#include "../includes/lem_in.h"

static void delete_node(t_paths **head_ref, int key)
{
	t_paths* temp = *head_ref, *prev;
	int	cnt = 0;

	if (temp != NULL && cnt == key)
	{
		*head_ref = temp->next;   // Changed head
		free(temp);               // free old head
		return;
	}

	while (temp != NULL && cnt != key)
	{
		prev = temp;
		temp = temp->next;
		cnt++;
	}

	if (temp == NULL) return;
	prev->next = temp->next;

	free(temp);
}

static int delete_unused_paths(t_paths **head)
{
	t_paths	*curr;
	int		changed;
	int		cnt;

	changed = 0;
	curr = *head;
	while (curr)
	{
		if (curr->predicted_ants <= 0)
		{
			changed = 1;
			delete_node(head, cnt);
			curr = *head;
			cnt = 0;
		}
		cnt++;
		curr = curr->next;
	}
	return (changed);
}

static void calculate_ants(t_paths *head, t_graph *g, int debug)
{
	t_paths *curr;

	curr = head;

	while (curr)
	{
		curr->predicted_ants = compute_ants(head, curr, g);
		if (debug) ft_fprintf(2, "{y}nb_ants = %f{R}\n", curr->predicted_ants);
		curr = curr->next;
	}
}

t_paths *trim_paths(t_paths *head, t_env env, t_graph *g)
{
	merge_sort(&head);
	calculate_ants(head, g, env.debug);
	while (delete_unused_paths(&head) == 1)
	{
		if (env.debug) ft_fprintf(2, "Recalculating ants... \n");
		calculate_ants(head, g, env.debug);
	}
	return (head);
}
