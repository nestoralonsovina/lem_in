#include "../includes/avl.h"

static void	avl_free(t_avl_node *node)
{
	if (!node)
		return ;
	avl_node_free(node->left);
	avl_node_free(node->right);
	free(node);
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

int				avl_insert(t_avl *self, char *key, int index)
{
	t_avl_node *tmp;

	tmp = avl_insert_node(self->head, key, index);
	if (!tmp)
	{
		self->free(self);
		return (0);
	}
	self->head = tmp;
	return (1);
}

t_avl		avl_init(void)
{
	t_avl n;

	n.head = NULL;
	n.free = avl_free;
	n.insert = avl_insert;
	return (n);
}
