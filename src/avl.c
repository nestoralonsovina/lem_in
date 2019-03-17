#include "../includes/avl.h"

void	avl_free(t_avl_node *node)
{
	if (!node)
		return ;
	avl_free(node->left);
	avl_free(node->right);
	free(node);
}

t_avl_node	*new_avl_node(char *key, int index)
{
	t_avl_node	*node;

	node = malloc(sizeof(t_avl_node));
	node->height = 0;
	node->key = key;
	node->index = index;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

t_avl_node	*avl_search(t_avl_node *root, char *key)
{
	int 	value;

	if (!root)
		return (root);
	value = ft_strcmp(key, root->key);
	if (!value)
		return (root);
	if (value < 0)
		return (avl_search(root->right, key));
	return (avl_search(root->left, key));
}

int 		avl_get_index(t_avl_node *root, char *key)
{
	t_avl_node *n = avl_search(root, key);

	if (n)
		return (n->index);
	return (-1);
}

t_avl		avl_init(void)
{
	t_avl n;

	n.head = NULL;
	n.free = avl_free;
	n.insert = avl_insert;
	n.search = avl_search;
	n.get_index = avl_get_index;
	return (n);
}
