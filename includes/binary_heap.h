#ifndef BINARY_HEAP_H
#define BINARY_HEAP_H

#include <stdlib.h>

typedef struct	s_element
{
	int			id;
	int			priority;
}				t_element;

typedef struct	s_binary_heap
{
	int			n;
	t_element	*elements;
	int			*pos;
	int			(*smallest)(struct s_binary_heap *self);
	void		(*insert)(struct s_binary_heap *self, int id, int priority);
	void		(*decrease_key)(struct s_binary_heap *self, int id, int np);
	int			(*is_empty)(struct s_binary_heap *self);
}				t_binary_heap;

t_binary_heap	bh_init(int capacity);
int				bh_smallest(struct s_binary_heap *bh);
void			bh_insert(struct s_binary_heap *bh, int id, int priority);
void			bh_decrease_key(struct s_binary_heap *bh, int id, int new_priority);
int				bh_is_empty(struct s_binary_heap *bh);

#endif
