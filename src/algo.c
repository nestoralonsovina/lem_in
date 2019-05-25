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

typedef struct s_bfs
{
	t_queue q;
	t_edge **prev;
	int *dist;
	int *visited;
} t_bfs;

void init_bfs(t_bfs *bfs, int nodes)
{
	bfs->prev = malloc(sizeof(t_edge *) * (nodes + 1));
	bfs->visited = malloc(sizeof(int) * (nodes + 1));
	bfs->dist = malloc(sizeof(int) * (nodes + 1));
	if (!bfs->prev || !bfs->visited || !bfs->dist)
	{
		ft_fprintf(2, "Error: Malloc couldn't allocate the necessary memory\n");
		exit(EXIT_FAILURE);
	}
}

void bfs_reset_struct(t_bfs *bfs, int nodes, int src)
{
	int i;

	bfs->q = create_queue(nodes);
	if (!bfs->q.array)
	{
		ft_fprintf(2, "Error: Malloc couldn't allocate the necessary memory\n");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < nodes)
	{
		bfs->prev[i] = NULL;
		bfs->dist[i] = INT_MAX;
		bfs->visited[i] = false;
		i += 1;
	}
	bfs->visited[src] = 1;
	bfs->dist[src] = 0;
	bfs->q.push(&(bfs->q), src);
}

void bfs_run_iteration(t_bfs *bfs, t_graph *g)
{
	t_edge *tmp;
	int cur;
	int i;

	while (bfs->q.size != 0)
	{
		cur = bfs->q.pop(&(bfs->q));
		i = 0;
		while (i < (int)g->adj_list[cur]->nb_links)
		{
			tmp = g->adj_list[cur]->links[i];
			if (bfs->visited[tmp->to] == 0 && !tmp->visited)
			{
				bfs->dist[tmp->to] = bfs->dist[tmp->from] + 1;
				bfs->prev[tmp->to] = tmp;
				bfs->q.push(&(bfs->q), tmp->to);
				bfs->visited[tmp->to] = true;
			}
			i += 1;
		}
	}
	free(bfs->q.array);
}

void algo(t_env env, t_graph *g)
{
	int i;
	t_edge **tmp_path;
	t_paths *head = NULL;

	//main struct for bfs
	t_bfs bfs;

	init_bfs(&bfs, g->adj_vert);
	while (true)
	{
		bfs_reset_struct(&bfs, g->adj_vert, g->source.index);
		bfs_run_iteration(&bfs, g);
		if (bfs.prev[g->sink.index] == NULL)
		{
			break;
		}
		tmp_path = make_path(bfs.prev, bfs.dist[g->sink.index], g->sink.index);
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
		exit(EXIT_FAILURE);
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
