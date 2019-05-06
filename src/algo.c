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

static t_edge **make_path(t_edge **prev, int l, int d)
{
	t_edge **path = malloc(sizeof(t_edge *) * (l + 1));
	path[l--] = NULL;
	for (t_edge *e = prev[d]; e != NULL; e = prev[e->from]) {
		path[l--] = e;
	}
	return path;

}

static bool	path_already_visited(t_env env, t_paths *head, t_edge *cur)
{
	int i;
	int path_len;

	if (head != NULL)\
	{

		while (head)
		{
			i = 0;
			// (remainder) path->mc := len of the path
			path_len = len(head->path);	
			while (i < path_len)
			{

				// here we should be okay comparing pointers, since
				// they shouldn't have changed.
				if (head->path[i] == cur || head->path[i]->rev == cur /* we don't wanna go backwards neither? Don't know if this is right*/)
				{
					return (true);
				}
				i += 1;
			}
			head = head->next;
		}

	}
	return (false);
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
			while (i < g->adj_list[cur]->nb_links)
			{
				tmp = g->adj_list[cur]->links[i];
				if (visited[tmp->to] == 0\
						&& path_already_visited(env, head, tmp) == false)
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


		tmp_path = make_path(prev, dist[d], d);

		mc = mc + len(tmp_path);
		append_path(&head, new_path(tmp_path, count_paths(head) + 1, mc, g->nb_ant));


	} // end of MAIN loop

	if (env.debug) {

		t_paths *ptr = head;
		while (ptr != NULL)
		{
			ft_fprintf(2, "path: {g}");
			d_print_path(ptr->path, *g);
			ft_fprintf(2, "{R} {b}cost: %d | flow: %d{R} {y} time: %d{R}\n", ptr->mc, ptr->mf, ptr->time);
			ptr = ptr->next;
		}
	}


	/*
	** At this point we have a list of paths with it's lengths,
	** we can take the one that has the less time, and delete all the
	** paths afterwards.
	*/ 

	if (head == NULL)
	{
		// !error no paths found TODO: handle error message here
		exit (EXIT_FAILURE);
	}

	t_paths *best = NULL;

	// take the minimum cost
	
	t_paths *ptr;
	
	ptr = head;

	while (ptr)
	{
		if (!best)
		{
			best = ptr;
			continue ;
		}
		if (best->time > ptr->time)
		{
			best = ptr;
		}
		ptr = ptr->next;
	}

	// now delete everything that is after the best path

	ptr = best->next;
	while (ptr)
	{
		t_paths *tmp = NULL;
		tmp = ptr->next;
		free(ptr->path); // free the wrapper but not the edges, those are still saved.
		free(ptr);
		ptr = tmp;
	}
	best->next = NULL;

	if (env.debug) {
		ft_putendl_fd("------------------------------------", 2);
		t_paths *ptr = head;
		while (ptr != NULL)
		{
			ft_fprintf(2, "path: {g}");
			d_print_path(ptr->path, *g);
			ft_fprintf(2, "{R} {b}cost: %d | flow: %d{R} {y} time: %d{R}\n", ptr->mc, ptr->mf, ptr->time);
			ptr = ptr->next;
		}
	}

	// TODO: show map information if we found a solution
	play(env, g, head);

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
