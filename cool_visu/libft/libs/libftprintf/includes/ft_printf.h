/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbally <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 14:09:08 by hbally            #+#    #+#             */
/*   Updated: 2019/01/25 18:53:02 by hbally           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <string.h>
# include <stdint.h>

# define ARG_FOUND 0
# define NO_ARG_FOUND 1

# define NO_FMT_STRING -1
# define BAD_FD -2

typedef struct		s_index
{
	uint8_t			asprintf;
	int				fd;
	char			*buf;
	size_t			head;
	size_t			head_old;
	size_t			fmt_head;
	size_t			fmt_head_old;
	int				error;
	char			type;
	int				length;
	long long		precision;
	long long		width;
	int				flags;
	int				negative;
	size_t			size;
}					t_index;

int					ft_printf(const char *format, ...);
int					ft_dprintf(int fd, const char *format, ...);
int					ft_asprintf(char **ret, const char *format, ...);
int					parser(const char *format, t_index *params, va_list *args);
int					dispatcher(char c, va_list *args, t_index *params);

int					baker_char(char c, t_index *params);
int					baker_string(char *s, t_index *params);
int					baker_pointer(void *p, t_index *params);
int					baker_int(int n, t_index *params);
int					baker_long(long n, t_index *params);
int					baker_longlong(long long n, t_index *params);
int					baker_double(double n, t_index *params);
int					baker_longdouble(long double n, t_index *params);

void				write_buff(const char *to_add, size_t len, t_index *params);
void				printer_arg(const char *s, const char c, t_index *params);
void				printer_fmt(const char *format,
								t_index *params,
								va_list *args);
void				printer_filler(char c, long long len, t_index *params);
void				special_handler(const char *s,
									const char c,
									t_index *params);
int					prefix(t_index *params,
						const char *s,
						const char type,
						int print);
int					width(const char *s,
							const char c,
							t_index *params,
							int print);
void				int_precision(t_index *params);
int					float_precision(const char *s, t_index *params);
size_t				find_point(const char *s);

int					check_flag(const char c, t_index *params);
int					check_length(const char *format,
									size_t *head,
									t_index *params);
int					check_width(const char *format,
									size_t *head,
									t_index *params,
									va_list *args);
int					check_precision(const char *format,
									size_t *head,
									t_index *params);
void				reset(t_index *params);
int					exit_clean(char **ret, t_index *params);
int					set_errno(int error);

#endif
