#include "../includes/binary_heap.h"

/**
 * Return the vertex identifier of the smallest vertex in heap and
 * readjust the heap
 * @return smallest vertex in heap
 */

int				bh_smallest(struct s_binary_heap *self)
{
	t_element	last;
	t_element	sm;
	int			id;
	int			pidx;
	int			child;

	id = self->elements[1].id;
	last = self->elements[self->n];
	self->n -= 1;

	self->elements[1] = last;

	pidx = 1;
	child = pidx * 2;
	while (child < self->n)
	{
		// select smaller of two children
		sm = self->elements[child];
		if (child + 1 < self->n) {
			if (sm.priority > self->elements[child + 1].priority)
				sm = self->elements[++child];
		}

		if (last.priority <= sm.priority)
			break ;

		self->elements[pidx] = sm;
		self->pos[sm.id] = pidx;

		pidx = child;
		child = 2 * pidx;
	}
	self->elements[pidx] = last;
	self->pos[last.id] = pidx;
	return (id);
}

/**
 * Insert the given value into the tree with priority. Ties are broken
 * in favor of insert.
 * @param id id information to be stored
 * @param priority priority to associate with this id
 */

void			bh_insert(struct s_binary_heap *self, int id, int priority)
{
	int	i;
	t_element p;
	int	pidx;

	// add to end of heap
	i = ++(self->n);
	while (i > 1)
	{
		pidx = i/2;
		p = self->elements[pidx];

		// if we're in the right spot leave loop
		if (priority > p.priority)
			break ;

		// swap and continue otherwise
		self->elements[i] = p;
		self->pos[p.id] = i;
		i = pidx;
	}

	// insert into spot vacated by moved element (or last one)
	self->elements[i].id = id;
	self->elements[i].priority = priority;
	self->pos[i] = i;
}

/**
 * Find the vertex with the identifier [id] and reduce its priority to the
 * given value. It is the responsibility of the caller to ensure that this
 * function is only invoked when new_priority is indeed smaller than
 * the existing priority associated with the id
 * @param id information to have the priority reduced
 * @param new_priority priority which must be smaller than existing priority
 */

void			bh_decrease_key(struct s_binary_heap *self,
		int id, int new_priority)
{
	int size;

	// save the size
	size = self->n;

	// truncate the heap and act like the binary heap up to but
	// not including this one is all that exists
	self->n = self->pos[id] - 1;

	// now we insert and the binary heap is shuffled appropriately
	self->insert(self, id, new_priority);

	// since the new_priority must be lower, we can expand back
	// and we still have a working binary heap
	self->n = size;
}

/**
 * @return true if the bh is empty, false if not
 */

int				bh_is_empty(struct s_binary_heap *self)
{
	return (self->n == 0);
}

t_binary_heap	bh_init(int capacity)
{
	t_binary_heap n;

	n.n = 0;
	n.elements = (t_element *)malloc(sizeof(t_element) * (capacity + 1));
	n.pos = (int *)malloc(sizeof(int) * (capacity + 1));
	n.smallest = bh_smallest;
	n.insert = bh_insert;
	n.is_empty = bh_is_empty;
	n.decrease_key = bh_decrease_key;
	return (n);
}
