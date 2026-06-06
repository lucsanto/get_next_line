#include "get_next_line_bonus.h"

int	newline_not_found(char *str)
{
	if (!str)
		return (1);
	while (*str)
	{
		if (*str == '\n')
			return (0);
		str++;
	}
	return (1);
}

char	*init_empty(void)
{
	char	*str;

	str = malloc(sizeof(char));
	if (!str)
		return (NULL);
	str[0] = '\0';
	return (str);
}

char	*join_to_total(char *total, char *buffer)
{
	char	*final;
	size_t	i;
	size_t	j;

	if (!total)
		total = init_empty();
	if (!total)
		return (NULL);
	final = malloc(ft_strlen(total) + ft_strlen(buffer) + 1);
	if (!final)
		return (free_null(total));
	i = 0;
	while (total[i])
	{
		final[i] = total[i];
		i++;
	}
	j = 0;
	while (buffer[j])
		final[i++] = buffer[j++];
	final[i] = '\0';
	free(total);
	return (final);
}

char	*extract_line(char *total)
{
	char	*temp;
	size_t	i;
	size_t	j;

	i = 0;
	if (!total)
		return (NULL);
	while (total[i] != '\n' && total[i])
		i++;
	if (total[i] == '\0')
		temp = (char *)malloc(sizeof(char) * (i + 1));
	else
		temp = (char *)malloc(sizeof(char) * (i++ + 2));
	if (!temp)
		return (NULL);
	j = 0;
	while (j < i)
	{
		temp[j] = total[j];
		j++;
	}
	temp[j] = '\0';
	return (temp);
}

char	*save_rest(char *total)
{
	char	*rest;
	size_t	i;
	size_t	j;

	if (!total)
		return (NULL);
	i = 0;
	while (total[i] && total[i] != '\n')
		i++;
	if (!total[i] || !total[i + 1])
	{
		free(total);
		return (NULL);
	}
	rest = malloc(sizeof(char) * (ft_strlen(total + i + 1) + 1));
	if (!rest)
	{
		free(total);
		return (NULL);
	}
	i++;
	j = 0;
	while (total[i])
		rest[j++] = total[i++];
	rest[j] = '\0';
	free(total);
	return (rest);
}