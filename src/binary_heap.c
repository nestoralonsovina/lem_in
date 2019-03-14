#include "../includes/lem_in.h"

typedef struct	s_element
{
	int			id;
	int			priority;
}				t_element;

typedef struct	s_binary_heap
{
	int			n = 0;
	t_element	*elements;
	int			*pos;

	(int)		(*smallest) (struct s_binary_heap *);
	(void)		(*insert) (struct s_binary_heap *, int, int);
	(void)		(*decrease_key) (struct s_binary_heap *, int, int)
	(t_bool)	(*is_empty) (struct s_binary_heap *)
}				t_binary_heap;

/**
 * Return the vertex identifier of the smallest vertex in heap and
 * readjust the heap
 * @return smallest vertex in heap
 */

int				bh_smallest(struct s_binary_heap *bh) {
	t_element	last;
	t_element	sm;
	int			id;
	int			pidx;
	int			child;

	id = bh->elements[1].id;
	last = bh->elements[bh->n];
	bh->n -= 1;

	bh->elements[1] = last;

	pidx = 1;
	child = pidx * 2;
	while (child < bh->n)
	{
		// select smaller of two children
		sm = bh->elements[child];
		if (child + 1 < bh->n) {
			if (sm.priority > bh->elements[child + 1].priority)
				sm = bh->elements[++child];
		}

		if (last.priority <= sm.priority)
			break ;

		bh->elements[pidx] = sm;
		bh->pos[sm.id] = pidx;

		pidx = child;
		child = 2 * pidx;
	}
	bh->elements[pidx] = last;
	bh->pos[last.id] = pidx;
	return (id);
}

/**
 * Insert the given value into the tree with priority. Ties are broken
 * in favor of insert.
 * @param id id information to be stored
 * @param priority priority to associate with this id
 */

void			bh_insert(struct s_binary_heap *bh,
		int id, int priority)
{
	int	i;
	t_element p;
	int	pidx;

	// add to end of heap
	i = ++(bh->n);
	while (i > 1)
	{
		pidx = i/2;
		p = bh->elements[pidx];

		// if we're in the right spot leave loop
		if (priority > p.priority)
			break ;

		// swap and continue otherwise
		bh->elements[i] = p;
		bh->pos[p.id] = i;
		i = pidx;
	}

	// insert into spot vacated by moved element (or last one)
	bh->elements[i].id = id;
	bh->elements[i].priority = priority;
	bh->pos[i] = i;
}

/**
 * Find the vertex with the identifier [id] and reduce its priority to the
 * given value. It is the responsibility of the caller to ensure that this
 * function is only invoked when new_priority is indeed smaller than
 * the existing priority associated with the id
 * @param id information to have the priority reduced
 * @param new_priority priority which must be smaller than existing priority
 */

void			bh_decrease_key(struct s_binary_heap *bh,
		int id, int new_priority)
{
	int size;

	// save the size
	size = bh->n;

	// truncate the heap and act like the binary heap up to but
	// not including this one is all that exists
	bh->n = bh->pos[id] - 1;

	// now we insert and the binary heap is shuffled appropriately
	bh.insert(id, new_priority);

	// since the new_priority must be lower, we can expand back
	// and we still have a working binary heap
	bh->n = size;
}

/**
 * @return true if the bh is empty, false if not
 */

t_bool			bh_is_empty(struct s_binary_heap *bh)
{
	return (bh->n == 0);
}

t_binary_heap	bh_init(int capacity)
{
	t_binary_heap n;

	n.elements = (t_element *)malloc(sizeof(t_element) * (capacity + 1));
	n.pos = (int *)malloc(sizeof(int) * (capacity + 1));
	n.smallest = bh_smallest;
	n.insert = bh_insert;
	n.is_empty = bh_is_empty;
	n.decrease_key = bh_decrease_key;
	return (n);
}
