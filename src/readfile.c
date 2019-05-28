/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readfile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jallen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 14:37:40 by jallen            #+#    #+#             */
/*   Updated: 2019/05/14 14:37:49 by jallen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

static char	*readfile(char *str, int fd)
{
	char		buff[BUFF_SIZE + 1];
	char		*ptr;
	int			ret;

	while ((ret = read(fd, buff, BUFF_SIZE)) > 0)
	{
		ptr = str;
		buff[ret] = '\0';
		str = ft_strjoin(str, buff);
		free(ptr);
	}
	return (str);
}

int			check_end(char **src, char **line)
{
	size_t	i;
	char	*str;

	str = *src;
	i = 0;
	if (str[i])
	{
		while (str[i] != '\n' && str[i])
			i++;
		if (i == 0)
			(*line) = NULL;
		else
		{
			*line = ft_strsub(str, 0, i);
			str += i + 1;
		}
		*src = str;
		return (1);
	}
	return (0);
}

int			lem_in_gnl(char **line, int return_file)
{
	static char	*str;
	static char *ptr;
	size_t		i;

	if (line == NULL || read(0, &i, 0) < 0 || BUFF_SIZE <= 0)
		return (-1);
	if (!str && !(str = malloc(sizeof(char) * (BUFF_SIZE + 1))))
		return (-1);
	str = readfile(str, 0);
	if (!ptr && !(ptr = str))
		return (-1);
	if (return_file)
	{
		*line = ptr;
		return (1);
	}
	if (check_end(&str, line) == 1)
		return (1);
	return (0);
}
