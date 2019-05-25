#include "../includes/lem_in.h"
#include <limits.h>
#include <stdbool.h>

static int sum_lengths(t_paths *head)
{
	if (!head)
		return 0;
	return head->len + sum_lengths(head->next);
}

double compute_ants(t_paths *head, t_paths *cur, t_graph *g)
{
	int nb_paths = count_paths(head);
	int nb_len_otherpaths = sum_lengths(head) - cur->len;
	return (g->nb_ant - ((count_paths(head) - 1) * cur->len - (sum_lengths(head) - cur->len))) / nb_paths;
}

void	algo(t_env env, t_graph *g)
{
	// n -> number of nodes, s -> index of source, d -> index of destination
	int n = g->adj_vert;
	int s = g->source.index;
	int d = g->sink.index;

	// iterators and counters
	int		i;
	int		mc = 0;
	int		cur;
	t_edge	*tmp;

	// saved paths
	t_edge  **tmp_path;
	t_paths *head = NULL;

	while (true)
	{
		// create a queue for the BFS
		t_queue q = create_queue(n);

		// basic arrays for each bfs iterations
		t_edge *prev[n];
		int dist[n];
		int visited[n];

		// set default values
		i = 0;
		while (i < n)
		{
			prev[i] = NULL;
			dist[i] = INT_MAX;
			visited[i] = false;
			i += 1;
		}

		// whitelist source
		visited[s] = 1;
		dist[s] = 0;
		q.push(&q, s);

		// run BFS
		while (q.size != 0)
		{
			cur = q.pop(&q);
			i = 0;
			while (i < (int)g->adj_list[cur]->nb_links)
			{
				tmp = g->adj_list[cur]->links[i];
				if (visited[tmp->to] == 0\
						&& !tmp->visited)
				{
					dist[tmp->to] = dist[tmp->from] + 1;
					prev[tmp->to] = tmp;
					q.push(&q, tmp->to);
					visited[tmp->to] = true;
				}
				i += 1;
			}
		}
		free(q.array);
		if (prev[d] == NULL)
		{
			break;
		}

		tmp_path = make_path(prev, dist[d], d);
		i = 0;
		while (tmp_path[i])
		{
			tmp_path[i]->visited = 1;
			i += 1;
		}

		if (path_repeated(head, tmp_path) == false)
		{
			path_goes_backwards(head, tmp_path, g);
			append_path(&head, new_path(tmp_path));
		}
	}

	if (head == NULL)
	{
		ft_fprintf(2, "ERROR\n"); // this works
		exit (EXIT_FAILURE);
	}

	char *file;

	lem_in_gnl(&file, 1);

	head = trim_paths(head, env, g);
	head = delete_superposition(head, env, g);
	head = trim_paths(head, env, g);

	play(g, head);

	while (head)
	{
		t_paths *tmp = head->next;
		free(head->path);
		int i = 0;
		int j = head->move[0]->len;
		while (i < j)
		{
			free(head->move[i]);
			i += 1;
		}
		free(head->move);
		free(head);
		head = tmp;
	}
}
