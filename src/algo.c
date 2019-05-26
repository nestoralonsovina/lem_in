/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalonso <nalonso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 17:46:54 by nalonso           #+#    #+#             */
/*   Updated: 2019/05/25 17:47:37 by nalonso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	algo_manage_path(t_bfs *bfs, t_graph *g, t_paths **head)
{
	int		i;
	t_edge	**tmp_path;

	i = 0;
	tmp_path = make_path(bfs->prev, bfs->dist[g->sink.index], g->sink.index);
	while (tmp_path[i])
	{
		tmp_path[i]->visited = 1;
		i += 1;
	}
	if (path_repeated(*head, tmp_path) == 0)
	{
		path_goes_backwards(*head, tmp_path);
		append_path(head, new_path(tmp_path));
	}
}

void	print_file(void)
{
	char	*file;

	lem_in_gnl(&file, 1);
	ft_printf("%s\n", file);
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

#include <time.h>

void	algo(t_env env, t_graph *g)
{
	t_bfs	bfs;
	t_paths	*head;
   
	head = NULL;
	bfs_init(&bfs, g->adj_vert);
	while (42)
	{
		bfs_reset_struct(&bfs, g->adj_vert, g->source.index);
		bfs_run_iteration(&bfs, g);
		if (bfs.prev[g->sink.index] == NULL)
		{
			break ;
		}
		algo_manage_path(&bfs, g, &head);
	}
	bfs_free(&bfs);
	if (head == NULL)
	{
		ft_fprintf(2, "ERROR\n");
		exit(EXIT_FAILURE);
	}
	print_file();
	head = trim_paths(head, env, g);
	head = delete_superposition(head, env, g);
	head = trim_paths(head, env, g);
	play(g, head);
}
