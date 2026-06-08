#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//mandatory
#include "get_next_line.h"

//bonus
//#include "get_next_line_bonus.h"

void	print_gnl(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		printf("%s\n", line);
		free(line);
		line = get_next_line(fd);
	}
}

int	main(void)
{
	int	fd1;
	// int	fd2;

	printf("-------mandatory-------\n");
	fd1 = open("a.txt", O_RDONLY);
	if (fd1 < 0)
		return (1);
	print_gnl(fd1);
	close(fd1);

	// printf("\n------fd inválido-------\n");
	// if (get_next_line(-1) == NULL)
	// 	printf("fd invalido retornou NULL\n");

	// printf("\n-------bonus-------\n");
	// fd1 = open("a.txt", O_RDONLY);
	// fd2 = open("b.txt", O_RDONLY);
	// if (fd1 < 0 || fd2 < 0)
	// 	return (1);

	// printf("fd1: %s", get_next_line(fd1));
	// printf("fd2: %s", get_next_line(fd2));
	// printf("fd1: %s", get_next_line(fd1));
	// printf("fd2: %s", get_next_line(fd2));
	// printf("fd1: %s", get_next_line(fd1));
	// printf("fd2: %s", get_next_line(fd2));

	// close(fd1);
	// close(fd2);
	// printf("\n");
	
	// printf("\n------teste stdin / fd 0-------\n");
	// printf("Digite algumas linhas e aperte Ctrl+D para finalizar:\n");

	// char *line;

	// line = get_next_line(0);
	// while (line)
	// {
	// 	printf("linha lida: %s", line);
	// 	free(line);
	// 	line = get_next_line(0);
	// }
	return (0);
}
