#include "../includes/lem_in.h"

void	**realloc_tab(void **ptr, size_t new_size, size_t original_size)
{
	void	**new;

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	else if (!ptr)
		return (malloc(new_size));
	else if (new_size <= original_size)
		return (ptr);
	else
	{
		new = malloc(new_size);
		if (new)
		{
			for (size_t i = 0; i < original_size; i++)
				new[i] = ptr[i];
			free(ptr);
		}
		return (new);
	}
}

void	init_dtab(t_dtab *a, size_t initial_size)
{
	a->array = (char **)malloc(initial_size * sizeof(char *));
	a->used = 0;
	a->size = initial_size;
}

void	insert_dtab(t_dtab *a, char *element)
{
	int	tmp;

	if (a->used + 1 == a->size)
	{
		tmp = a->size;
		a->size *= 2;
		a->array = (char **)realloc_tab((void **)a->array, a->size * sizeof(char *), tmp);
	}
	a->array[a->used++] = element;
	a->array[a->used] = NULL;
}

void	free_dtab(t_dtab *a)
{
	char	**ptr;

	ptr = a->array;
	while (a->used--)
	{
		free(*ptr);
		ptr += 1;
	}
	free(a->array);
	a->array = NULL;
	a->used = 0;
	a->size = 0;
}
