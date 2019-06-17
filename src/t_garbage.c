#include "../includes/lem_in.h"
#include <unistd.h>

static void		priv_gb_fail(t_garbage *gb)
{
	write(2, "Memory allocation failed, terminating.\n", 40);
	gb_freeall(gb);
	exit(EXIT_FAILURE);
}

static void		priv_gb_extend(t_garbage *gb)
{
	void	*tmp;
	size_t	o_size;

	o_size = gb->mem_len;
	if (gb->mem_len)
		gb->mem_len *= 2;
	else
		gb->mem_len = 10;
	tmp = ft_realloc(gb->pointers,\
		gb->mem_len * sizeof(*gb->pointers), o_size * sizeof(*gb->pointers));
	if (!tmp)
		priv_gb_fail(gb);
	gb->pointers = tmp;
	ft_bzero(&gb->pointers[gb->arr_len], gb->mem_len - gb->arr_len);
}

t_garbage		gb_init(void)
{
	t_garbage	gbc;

	gbc.arr_len = 0;
	gbc.mem_len = 10;
	gbc.pointers = ft_memalloc(gbc.mem_len * sizeof(*gbc.pointers));
	if (!gbc.pointers)
	{
		write(2, "Memory allocation failed, terminating.\n", 40);
		exit(EXIT_FAILURE);
	}
	return (gbc);
}

void			gb_freeall(t_garbage *gb)
{
	size_t	i;

	i = 0;
	while (i < gb->arr_len)
	{
		free(gb->pointers[i]);
		++i;
	}
	free(gb->pointers);
	gb->pointers = NULL;
	gb->arr_len = 0;
	gb->mem_len = 0;
}

void			*gb_malloc(t_garbage *gb, size_t size)
{
	if (gb->arr_len == gb->mem_len - 1)
		priv_gb_extend(gb);
	gb->pointers[gb->arr_len] = malloc(size);
	if (!gb->pointers[gb->arr_len])
		priv_gb_fail(gb);
	return (gb->pointers[gb->arr_len++]);
}

