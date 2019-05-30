/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalonso <nalonso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 17:46:54 by nalonso           #+#    #+#             */
/*   Updated: 2019/05/29 15:15:29 by jallen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int		algo_manage_path(t_bfs *bfs, t_graph *g, t_paths **head, int debug, int bg)
{
	t_edge	**tmp_path;
	double	last;

	tmp_path = make_path(bfs->prev, bfs->dist[g->sink.index], g->sink.index);
	if (bg)
	{
		path_goes_backwards(*head, tmp_path);			
	}
	append_path(head, new_path(tmp_path));
	last = calculate_ants(*head, g, debug);

	return (1);
}

void	print_file(int debug)
{
	char	*file;

	lem_in_gnl(&file, 1);
	if (!debug)
		ft_printf("%s\n", file);
	free(file);
}
void	free_paths(t_paths *head)
{
	t_paths *tmp;
	int		i;
	int		j;

	while (head)
	{
		tmp = head->next;
		free(head->path);
		i = 0;
		j = head->move[0]->len;
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

int		ft_min(int a, int b)
{
	return (a < b ? a : b);
}

void	algo(t_env env, t_graph *g)
{
	t_bfs	bfs;
	t_paths	*head;
	int		flow;

	head = NULL;
	bfs_init(&bfs, g->adj_vert);
	flow = 0;
	while (42)
	{
		bfs_reset_struct(&bfs, g->adj_vert, g->source.index);
		bfs_run_iteration(&bfs, g);
		if (bfs.prev[g->sink.index] == NULL)
		{
			break ;
		}

		// after iterating with BoyFriendS, we go through the augmenting path and
		// set the new flow through it, in our case, blocking it, afterwards
		// we'll handle if the path goes backwards to "liberate" the flow 
		// through the whole path (we might have the boolean here)

		int df = 2147483647;
		int bg = 0;

		// we found an augmenting path, we see how much flow we can send through
		// it, (in our case should always be 1, but just to be sure for the moment).
		for (t_edge *e = bfs.prev[g->sink.index]; e != NULL; e = bfs.prev[e->from])
		{
			df = ft_min(df, e->cap - e->flow);
		}
		// we update the edges by that amount
		for (t_edge *e = bfs.prev[g->sink.index]; e != NULL; e = bfs.prev[e->from])
		{
			e->flow = e->flow + df;
			e->rev->flow = e->rev->flow - df;
			// if a path goes backwards, it flow after passing through it should be 0,
			// a process known as "cancelling flow"
			if (e->flow == 0 && e->rev->flow == 0)
			{
				if (env.debug) ft_fprintf(2, "{r} path goes backwards {R}\n");
				bg = 1;
			}
		}
		flow = flow + df;

		if (algo_manage_path(&bfs, g, &head, env.debug, bg) == 0)
			break ;
	}
	if (env.debug) ft_fprintf(2, "{y} number of paths: %d{R}\n", count_paths(head));
	bfs_free(&bfs);
	if (env.debug) d_print_paths(head, g);
	if (head == NULL)
	{
		ft_fprintf(2, "ERROR\n");
		exit(EXIT_FAILURE);
	}
	print_file(env.debug);
	head = delete_superposition(head, g);
	head = trim_paths(head, env, g);
	head = trim_paths(head, env, g);
	if (env.debug) d_print_paths(head, g);
	play(g, head);
	free_paths(head);
}
