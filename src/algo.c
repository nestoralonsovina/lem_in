#include "../includes/lem_in.h"
#include <limits.h>
#include <stdbool.h>

void p_array(int *a, int l) {
	for (int i = 0; i < l; i++) ft_printf("%d ", a[i]);
	ft_putendl(0);
}

static int len(t_edge **a) {
	int i = 0;
	while (a[i])
		i++;
	return i;
}

static int list_len(t_paths *l)
{
	if (!l)
		return 0;
	return 1 + list_len(l->next);
}

int sum_lengths(t_paths *l)
{
	if (!l)
		return 0;
	return l->len + 1 + sum_lengths(l->next);
}

double compute_ants(t_paths *head, t_paths *cur, int ants)
{
	int nb_paths = list_len(head);
	return ((ants - ((nb_paths - 1) * (cur->len + 1) - (sum_lengths(head) - (cur->len + 1)))) / nb_paths);
}

static t_edge **make_path(t_edge **prev, int l, int d)
{
	t_edge **path = malloc(sizeof(t_edge *) * (l + 1));
	path[l--] = NULL;
	for (t_edge *e = prev[d]; e != NULL; e = prev[e->from]) {
		path[l--] = e;
	}
	return path;
}

static void unvisit_path(t_edge **path, t_edge *intersection)
{
	int i;

	i = 0;
	while (path[i])
	{
		if (path[i] != intersection)
		{
			path[i]->visited = 0;
		}
		i += 1;
	}
}

static bool path_repeated(t_paths *head, t_edge **tmp)
{
	int i;

	while (head)
	{
		i = 0;
		while (head->path[i] && tmp[i] && head->path[i] == tmp[i])
		{
			i += 1;
		}
		if (!head->path[i] && !tmp[i])
			return (true);
		head = head->next;
	}
	return (false);
}

static bool path_goes_backwards(t_paths *head, t_edge **tmp, t_graph *g)
{
	int i;
	int j;
	int p_len;

	p_len = len(tmp);
	while (head)
	{
		i = 0;
		while (i < head->len)
		{
			j = 0;
			while (j < p_len)
			{
				if (head->path[i]->rev == tmp[j])
				{
					unvisit_path(head->path, head->path[i]);
					unvisit_path(tmp, head->path[i]);
					head->parent = 1;
					return (true);
				}
				j += 1;
			}
			i += 1;
		}
		head = head->next;
	}
	return (false);
}

t_edge **push_edge(t_edge **path, t_edge *new_edge)
{
	int l;
	int i;
	t_edge **new;

	l = len(path);
	new = malloc(sizeof(*new) * (l + 1));
	if (!new)
		return (NULL);
	i = 0;
	if (path)
	{
		while (path[i])
		{
			new[i] = path[i];
			i += 1;
		}
	}
	new[i++] = new_edge;
	new[i] = NULL;
	return (new);
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
		} // end of BFS

		// exit the loop if no path was found in the last iteration of BFS
		free(q.array);
		if (prev[d] == NULL)
		{
			break;
		}

		/*
		 ** Since this is not EK or a network flow algorithm I'll describe what
		 ** values will be asigned to the different parameters.
		 **
		 ** Maximum flow: number of paths found up to this momment (the value asigned the first time is not relevant. I think?)
		 ** Minimum cost: length of the path
		 ** Time: same computation as always -> time := (ants / maxFlow) + minimumCost
		 **
		 ** The idea is that each path will have this three values, and then I'll take
		 ** the combination of paths that minimize the time based on the maximum flow
		 ** -> (number paths combining) and the minimum cost -> (lenght of the paths
		 ** being combined). Let's see if this works.
		 */

		/*
		 ** If the path goes backwards in another path, I will break the last one, that goes backwards
		 ** into two different paths, and substitute them.
		 */

		tmp_path = make_path(prev, dist[d], d);
		i = 0;
		while (tmp_path[i])
		{
			tmp_path[i]->visited = 1;
			i += 1;
		}

		if (path_repeated(head, tmp_path) == false)
		{
			int parent = path_goes_backwards(head, tmp_path, g);
			mc = len(tmp_path);
			append_path(&head, new_path(tmp_path, count_paths(head) + 1, mc, g->nb_ant, parent));
		}
	} // end of MAIN loop

	/*
	 ** At this point we have a list of paths with it's lengths,
	 ** we can take the one that has the less time, and delete all the
	 ** paths afterwards.
	 */

	if (head == NULL)
	{
		ft_fprintf(2, "ERROR");
		exit (EXIT_FAILURE);
	}

	char *file;

	// this call to the function will return all the information read previously
	// and return the original pointer
	lem_in_gnl(&file, 1);

	if (!env.debug)
		ft_printf("%s\n", file);
	free(file);

	if (env.debug) d_print_paths(head, g);

	head = trim_paths(head, env, g, g->nb_ant);
	head = delete_superposition(head, env, g);
	head = trim_paths(head, env, g, g->nb_ant);



	if (env.debug) d_print_paths(head, g);

	play(g, head, env);

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
