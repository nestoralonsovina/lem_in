/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbally <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 15:37:23 by hbally            #+#    #+#             */
/*   Updated: 2019/03/20 12:19:57 by hbally           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

static	int			ft_exit(int *j, int *size, int ret)
{
	*j = 0;
	*size = 0;
	return (ret);
}

static	int			ft_bufparse(char *buf, char **line, int fd)
{
	static int		i;
	static int		j;
	static int		size;
	static int		ret;

	if (i == 0)
		if ((ret = (int)read(fd, buf, GNL_BUFFSIZE)) < 1)
			return (ft_exit(&j, &size, (ret == -1 ? -1 : 0 + *line[0] != 0)));
	if (buf[0] == '\0')
		return (ft_exit(&j, &size, 0));
	while (i < ret && i < GNL_BUFFSIZE && buf[i] != '\n')
		(*line)[j++] = buf[i++];
	if (i == GNL_BUFFSIZE && buf[i - 1] != '\n')
	{
		size += GNL_BUFFSIZE;
		*line = (char*)ft_memrealloc(*line, size + 1, size + GNL_BUFFSIZE + 1);
		i = 0;
		if (!line)
			return (ft_exit(&j, &size, -1));
		return (ft_bufparse(buf, line, fd));
	}
	i = i < ret - 1 ? i + 1 : 0;
	return (ft_exit(&j, &size, 1));
}

int					get_next_line(const int fd, char **line)
{
	static char		*buf;
	int				ret;

	if (!buf)
		buf = (char*)ft_memalloc(GNL_BUFFSIZE);
	if (line)
		*line = (char*)ft_memalloc(GNL_BUFFSIZE + 1);
	if (!buf || !line || !*line || fd < 0)
	{
		if (buf)
			ft_memdel((void**)&buf);
		if (line && *line)
			ft_memdel((void**)line);
		return (-1);
	}
	ret = ft_bufparse(buf, line, fd);
	if (ret != 1)
	{
		ft_memdel((void**)&buf);
		ft_memdel((void**)line);
	}
	return (ret);
}
