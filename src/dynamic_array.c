/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamic_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalonso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 11:36:34 by nalonso           #+#    #+#             */
/*   Updated: 2019/02/22 12:19:30 by nalonso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

/*
** Set of functions that allow us to use a dynamic tab.
** @realloc_tab				Takes a ** pointer and allocates the new size,
**								copying the previous information.
** @init_dtab				Inits the dynamic tab to defaults values
** @index_dtab				Inserts element on specified index
** @insert_dtab				Inserts new element into the dynamic tab
** @free_dtab				Used to free the dynamic tab and it's elements.
*/

void	**realloc_tab(void **ptr, size_t new_size, size_t original_size)
{
	void	**new;
	size_t	i;

	i = -1;
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
			while (++i < original_size)
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

void	index_dtab(t_dtab *a, char *element, size_t index)
{
	int		tmp;
	char	*ptr;
	char	*ptr2;

	if (a->used + 1 == a->size)
	{
		tmp = a->size;
		a->size *= 2;
		a->array = (char **)realloc_tab((void **)a->array,\
				a->size * sizeof(char *), tmp);
	}
	ptr = a->array[index];
	a->array[index] = element;
	while (index < a->used)
	{
		ptr2 = a->array[index + 1];
		a->array[index + 1] = ptr;
		ptr = ptr2;
		index++;
	}
	a->array[++(a->used)] = NULL;
}

void	insert_dtab(t_dtab *a, char *element)
{
	int	tmp;

	if (a->used + 1 == a->size)
	{
		tmp = a->size;
		a->size *= 2;
		a->array = (char **)realloc_tab((void **)a->array,\
				a->size * sizeof(char *), tmp);
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
