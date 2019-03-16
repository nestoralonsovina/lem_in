#include "../includes/queue.h"

void		queue_push(struct s_queue *self, int item)
{
	if (self->size == self->capacity)
		return ;
	self->end = (self->end + 1) % self->capacity;
	self->array[self->end] = item;
	self->size = self->size + 1;
}

int			queue_pop(struct s_queue *self)
{
	int	item;

	if (self->size == 0)
		return (-1);
	item = self->array[self->start];
	self->start = (self->start + 1) % self->capacity;
	self->size = self->size - 1;
	return (item);
}

int			queue_front(struct s_queue *self)
{
	if (self->size == 0)
		return (-1);
	return (self->array[self->start]);
}

int			queue_rear(struct s_queue *self)
{
	if (self->size == 0)
		return (-1);
	return (self->array[self->end]);
}

t_queue		create_queue(size_t capacity)
{
	t_queue	queue;
	
	queue.capacity = capacity;
	queue.start = 0;
	queue.size = 0;
	queue.end = capacity - 1;
	queue.array = malloc(queue.capacity * sizeof(int));
	queue.pop = queue_pop;
	queue.front = queue_front;
	queue.rear = queue_rear;
	queue.push = queue_push;
	return (queue);
}