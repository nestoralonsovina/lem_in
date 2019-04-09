#ifndef AVL_H
#define AVL_H

#include "../libftprintf/includes/ft_printf.h"
#include <stdlib.h>

typedef struct s_avl_node
{
	int 				index;
	int 				height;
	unsigned long		key;
	struct s_avl_node	*left;
	struct s_avl_node	*right;
}				t_avl_node;

typedef struct s_avl
{
	t_avl_node	*head;

	int			(*insert)(struct s_avl *self, unsigned long key, int index);
	void		(*free)(t_avl_node *root);
	int 		(*get_index)(t_avl_node *root, unsigned long key);
}				t_avl;

t_avl_node		*new_avl_node(unsigned long key, int index);
int				avl_insert(t_avl *self, unsigned long key, int index);
int 			avl_get_index(t_avl_node *root, unsigned long key);
t_avl_node		*avl_search(t_avl_node *root, unsigned long key);
void			avl_free(t_avl_node *node);
t_avl			avl_init(void);

#endif
