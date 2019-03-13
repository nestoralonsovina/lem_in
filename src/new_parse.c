#include "../includes/lem_in.h"
#include <limits.h>

/*
 * Everything related to AVL tree
 */

int 	max(int a, int b)
{
	return ((a > b) ? a : b);
}

int 	avl_height(t_avl_node *n)
{
	if (n == NULL)
		return (0);
	return (n->height);
}

t_avl_node	*new_avl_node(char *key, int index)
{
	t_avl_node	*node;

	node = malloc(sizeof(t_avl_node));
	node->key = key;
	node->index = index;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

t_avl_node	*avl_right_rotate(t_avl_node *y)
{
	t_avl_node	*x;
	t_avl_node	*t2;

	x = y->left;
	t2 = x->right;

	x->right = y;
	y->left = t2;

	y->height = max(avl_height(y->left), avl_height(y->right));
	x->height = max(avl_height(x->left), avl_height(x->right));

	return (x);
}

t_avl_node	*avl_left_rotate(t_avl_node *x)
{
	t_avl_node	*y;
	t_avl_node	*t2;

	y = x->right;
	t2 = y->left;

	y->left = x;
	x->right = t2;

	x->height = max(avl_height(x->left), avl_height(x->right));
	y->height = max(avl_height(y->left), avl_height(y->right));

	return (x);
}

int 		avl_get_balance(t_avl_node *n)
{
	if (n == NULL)
		return (0);
	return (avl_height(n->left) - avl_height(n->right));
}

t_avl_node	*avl_insert(t_avl_node *node, char *key, int index)
{
	int	balance;
	int value;

	if (node == NULL)
		return (new_avl_node(key, index));

	value = ft_strcmp(key, node->key);
	if (value < 0)
		node->left = avl_insert(node->left, key, index);
	else if (value > 0)
		node->right = avl_insert(node->right, key, index);
	else // if the values are equal we return NULL
		return (NULL);

	node->height = 1 + max(avl_height(node->left), avl_height(node->right));
	balance = avl_get_balance(node);

	if (balance > 1 && value < 0)
		return (avl_right_rotate(node));

	if (balance < -1 && value > 0)
		return (avl_left_rotate(node));

	if (balance > 1 && value > 0)
	{
		node->left = avl_left_rotate(node->left);
		return (avl_right_rotate(node));
	}

	if (balance < -1 && value < 0)
	{
		node->right = avl_right_rotate(node->right);
		return (avl_left_rotate(node));
	}

	return (node);
}

int parse(t_env *env)
{
	char	*file[10000];
	int 	i;
	int		start;

	start = 0;
	i = 0;
	while (simple_gnl(&env->line) > 0)
	{
		if (ft_strchr(env->line, '-'))
			break ;
		if (env->line[0] != '#')
		{
			if (start == 1)
				env->i_start = env->graph.adj_vert;
			else if (start == 2)
				env->i_end = env->graph.adj_vert;
			env->head = avl_insert(env->head, env->line, env->graph.adj_vert);
			if (env->head == NULL)
				ft_printf("hello boiiiiiiiiiiiiiiiiiis\n");
		}
		else if (env->line[1] == '#')
		{
			if (ft_strequ(&env->line[2], "start"))
				start = 1;
			else if (ft_strequ(&env->line[2], "end"))
				start = 2;
		}
		file[i++] = env->line;
	}
	return (1);
}
