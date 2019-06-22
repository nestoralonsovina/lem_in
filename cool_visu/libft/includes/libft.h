/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbally <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 11:28:05 by hbally            #+#    #+#             */
/*   Updated: 2019/03/14 13:35:43 by hbally           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <stdint.h>
# include <time.h>

# define GNL_BUFFSIZE 1024

/*
** mem functions
*/

void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memset(void *b, int c, size_t len);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memchr(const void *s, int c, size_t n);
void				*ft_memalloc(size_t size);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				ft_memdel(void **ap);
void				ft_bzero(void *s, size_t n);
void				*ft_memrealloc(void *old, size_t old_size, size_t new_size);

/*
** string functions
*/

void				ft_strclr(char *s);
void				ft_strdel(char **as);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strnew(size_t size);
char				*ft_strstr(const char *haystack, const char *needle);
char				*ft_strchr(const char *s, int c);
int					ft_strchri(const char *s, const char c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strncat(char *s1, const char *s2, size_t n);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strncpy(char *dst, const char *src, size_t len);
char				*ft_strdup(const char *s1);
char				*ft_strcdup(const char *s1, char c);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s);
char				**ft_strsplit(char const *s, char c);
size_t				ft_strlen(const char *s);
int					ft_strclen(const char *s, const char c);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strnstr(const char *haystack,
									const char *needle, size_t len);
char				*ft_str_realloc(char *old, size_t size);

/*
** print functions
*/

int					ft_printf(const char *format, ...);
int					ft_dprintf(int fd, const char *format, ...);
int					ft_asprintf(char **ret, const char *format, ...);
void				ft_putendl(char const *s);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr(int n);
void				ft_putnbr_fd(int n, int fd);
void				ft_putstr(char const *s);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putchar(char c);
void				ft_putchar_fd(char c, int fd);

/*
** conversion functions
*/

char				*ft_itoa(int n);
char				*ft_uitoa(unsigned int n);
char				*ft_uitoxa(unsigned int n, int upper);
char				*ft_uitooa(unsigned int n);

char				*ft_ltoa(long n);
char				*ft_ultoa(unsigned long n);
char				*ft_ultoxa(unsigned long n, int upper);
char				*ft_ultooa(unsigned long n);

char				*ft_lltoa(long long n);
char				*ft_ulltoa(unsigned long long n);
char				*ft_ulltoxa(unsigned long long n, int upper);
char				*ft_ulltooa(unsigned long long n);

char				*ft_dtoa(double n);
char				*ft_ldtoa(long double n);
char				*ft_round_double(char *s, size_t p);

int					ft_atoi(const char *str);
long				ft_atol(const char *str);
long long			ft_atoll(const char *str);

/*
** misc functions
*/

int					get_next_line(const int fd, char **line);

int					ft_sqrt(int nb);
void				ft_int_swap(int *a, int *b);

int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);
int					ft_iswhitespace(int c);

int					ft_tolower(int c);
int					ft_toupper(int c);

int16_t				ft_abs16(int16_t n);
int32_t				ft_abs32(int32_t n);
int64_t				ft_abs64(int64_t n);
time_t				ft_abstime(time_t n);

#endif
