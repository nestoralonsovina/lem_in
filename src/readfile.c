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
	i = 0;
	if (str[i])
	{
		while (str[i] != '\n' && str[i])
			i++;
		if (i == 0)
			(*line) = ft_strdup("");
		else
		{
			*line = ft_strsub(str, 0, i);
			str += i + 1;
		}
		return (1);
	}
	return (0);
}
