#ifndef DTAB_H
# define DTAB_H

# include <stdlib.h>

typedef struct	s_dtab
{
	char	**array;
	size_t	used;
	size_t	size;
}				t_dtab;

void			init_dtab(t_dtab *a, size_t initial_size);
void			insert_dtab(t_dtab *a, char *element);
void			free_dtab(t_dtab *a);
void			index_dtab(t_dtab *a, char *element, size_t index);
void			**realloc_tab(void **ptr, size_t new_size, size_t original_size);

#endif
