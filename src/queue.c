#include "../includes/lem_in.h"

t_queue		*create_queue(size_t capacity)
{
	t_queue	*queue;
	
	queue = malloc(sizeof(t_queue));
	queue->capacity = capacity;
	queue->front = 0;
	queue->size = 0;
	queue->rear = capacity - 1;
	queue->array = malloc(queue->capacity * sizeof(int));
	return (queue);
}

void		enqueue(t_queue *queue, int item)
{
	if (queue->size == queue->capacity)
		return ;
	queue->rear = (queue->rear + 1) % queue->capacity;
	queue->array[queue->rear] = item;
	queue->size = queue->size + 1;
}

int			dequeue(t_queue *queue)
{
	int	item;

	if (queue->size == 0)
		return (-1);
	item = queue->array[queue->front];
	queue->front = (queue->front + 1) % queue->capacity;
	queue->size = queue->size - 1;
	return (item);
}

int			front(t_queue *queue)
{
	if (queue->size == 0)
		return (-1);
	return (queue->array[queue->front]);
}

int			rear(t_queue *queue)
{
	if (queue->size == 0)
		return (-1);
	return (queue->array[queue->rear]);
}

void		print_queue(t_queue *q)
{
	size_t i;

	i = q->front;
	ft_putstr("Printing queue: ");
	while (i < q->rear)
	{
		ft_printf("%d ", q->array[i]);
		i += 1;
	}
	ft_putendl(0);
}
