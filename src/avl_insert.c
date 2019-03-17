#include "../includes/avl.h"

static int 	avl_height(t_avl_node *n)
{
	if (n == NULL)
		return (0);
	return (n->height);
}

static int 		avl_get_balance(t_avl_node *n)
{
	if (n == NULL)
		return (0);
	return (avl_height(n->left) - avl_height(n->right));
}

static t_avl_node	*avl_right_rotate(t_avl_node *y)
{
	t_avl_node	*x;
	t_avl_node	*t2;

	x = y->left;
	t2 = x->right;
	x->right = y;
	y->left = t2;
	y->height = ft_max(avl_height(y->left), avl_height(y->right));
	x->height = ft_max(avl_height(x->left), avl_height(x->right));
	return (x);
}

static t_avl_node	*avl_left_rotate(t_avl_node *x)
{
	t_avl_node	*y;
	t_avl_node	*t2;

	y = x->right;
	t2 = y->left;
	y->left = x;
	x->right = t2;
	x->height = ft_max(avl_height(x->left), avl_height(x->right));
	y->height = ft_max(avl_height(y->left), avl_height(y->right));
	return (x);
}

static t_avl_node		*avl_insert_node(t_avl_node *node, char *key, int index)
{
	int	balance;
	int value;

	if (node == NULL)
		return (new_avl_node(key, index));

	value = ft_strcmp(key, node->key);
	if (value < 0)
		node->left = avl_insert_node(node->left, key, index);
	else if (value > 0)
		node->right = avl_insert_node(node->right, key, index);
	else
		return (NULL);

	node->height = 1 + ft_max(avl_height(node->left), avl_height(node->right));
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

int				avl_insert(t_avl *self, char *key, int index)
{
	t_avl_node *tmp;

	tmp = avl_insert_node(self->head, key, index);
	if (tmp == NULL)
	{
		self->free(self->head);
		return (0);
	}
	self->head = tmp;
	return (1);
}