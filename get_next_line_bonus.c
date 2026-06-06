#include "get_next_line_bonus.h"

char	*free_null(char *ptr)
{
	free(ptr);
	return (NULL);
}

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*read_to_total(int fd, char *total)
{
	int		bytes_read;
	char	*buffer;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (free_null(total));
	while (newline_not_found(total))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(buffer);
			return (free_null(total));
		}
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		total = join_to_total(total, buffer);
		if (!total)
			break ;
	}
	free(buffer);
	return (total);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*total[1024];

	if (fd < 0 || fd >= 1024 || BUFFER_SIZE < 1)
		return (NULL);
	if (read(fd, 0, 0) < 0)
	{
		free(total[fd]);
		total[fd] = NULL;
		return (NULL);
	}
	total[fd] = read_to_total(fd, total[fd]);
	line = extract_line(total[fd]);
	total[fd] = save_rest(total[fd]);
	if (line && line[0] == '\0')
	{
		free(line);
		return (NULL);
	}
	return (line);
}