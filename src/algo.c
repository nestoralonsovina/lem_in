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

int		count_bg(t_paths *head)
{
	if (!head)
		return 0;
	if (head->bg == 0)
		return 0 + count_bg(head->next);
	return 1 + count_bg(head->next);
}

int		algo_manage_path(t_bfs *bfs, t_graph *g, t_paths **head, int debug, int bg)
{
	t_edge	**tmp_path;
	static int para_tras = 0; 
	double	last;

	tmp_path = make_path(bfs->prev, bfs->dist[g->sink.index], g->sink.index);
	if (bg)
	{
		path_goes_backwards(*head, tmp_path);
		para_tras += 2;
	}
	else
		append_path(head, new_path(tmp_path, bg));
	last = calculate_ants(*head, g, debug);
	if (last <= 0 && para_tras < (count_paths(*head) - para_tras))
	{
		return (0);
	}
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

void	find_paths(t_env env, t_graph *g, t_paths **head_ref)
{
	t_paths	*head;
	t_bfs	bfs;
	int		bg;

	head = *head_ref;
	bfs_init(&bfs, g->adj_vert);
	while (42)
	{
		bfs_reset_struct(&bfs, g->adj_vert, g->source.index);
		bfs_run_iteration(&bfs, g);
		if (bfs.prev[g->sink.index] == NULL)
			break ;
		bg = 0;
		for (t_edge *e = bfs.prev[g->sink.index]; e != NULL; e = bfs.prev[e->from])
		{
			e->flow = e->flow + 1;
			e->rev->flow = e->rev->flow - 1;
			if (e->flow == 0 && e->rev->flow == 0)
			{
				if (env.debug) ft_fprintf(2, "{r} path goes backwards {R}\n");
				bg = 1;
			}
		}

		if (algo_manage_path(&bfs, g, &head, env.debug, bg) == 0)
			break ;
	}
	bfs_free(&bfs);
	*head_ref = head;
}

void	manage_extra_paths(t_env env, t_graph *g, t_paths **head)
{
	t_paths *tmp;
	int		cnt;

	tmp = *head;
	
	cnt = 0;
	while (tmp)
	{
		if (tmp->bg)
		{
			find_paths(env, g, head);
			cnt = 0;
		}
		cnt++;
		tmp = tmp->next;
	}
}

void	algo(t_env env, t_graph *g)
{
	t_paths	*head;

	head = NULL;
	find_paths(env, g, &head);
	manage_extra_paths(env, g, &head);
	if (env.debug) d_print_paths(head, g);
	if (head == NULL)
	{
		ft_fprintf(2, "ERROR\n");
		exit(EXIT_FAILURE);
	}
	print_file(env.debug);
	head = trim_paths(head, env, g);
	head = delete_superposition(head, g);
	head = trim_paths(head, env, g);
	if (env.debug) d_print_paths(head, g);
	play(g, head);
	free_paths(head);
}
