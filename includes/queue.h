#ifndef QUEUE_H
#define QUEUE_H

# include <stdlib.h>

typedef struct s_queue
{
	size_t		size;
	size_t		capacity;
	int			end;
	int			start;
	int			*array;
	void		(*push)(struct s_queue *self, int item);
	int 		(*pop)(struct s_queue *self);
	int 		(*front)(struct s_queue *self);
	int 		(*rear)(struct s_queue *self);
}				t_queue;

t_queue			create_queue(size_t capacity);
void			queue_push(t_queue *queue, int item);
int				queue_pop(t_queue *queue);
int				queue_front(t_queue *queue);
int				queue_rear(t_queue *queue);

#endif
