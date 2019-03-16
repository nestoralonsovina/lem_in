#ifndef AVL_H
#define AVL_H

#include "../libftprintf/includes/ft_printf.h"
#include <stdlib.h>

typedef struct s_avl_node
{
	int 				index;
	int 				height;
	char 				*key;
	struct s_avl_node	*left;
	struct s_avl_node	*right;
}				t_avl_node;

typedef struct s_avl
{
	t_avl_node	*head;

	int			(*insert)(struct s_avl *self, char *key, int index);
	void		(*free)(struct s_avl_node *head);
}				t_avl;

int				avl_insert(t_avl *self, char *key, int index);
t_avl_node		*avl_insert_node(t_avl_node *node, char *key, int index);
t_avl_node		*new_avl_node(char *key, int index);

#endif
