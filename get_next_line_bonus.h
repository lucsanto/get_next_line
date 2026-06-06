#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <unistd.h>
# include <stdlib.h>

size_t	ft_strlen(char *str);
char	*free_null(char *ptr);
char	*read_to_total(int fd, char *total);
char	*get_next_line(int fd);

int	    newline_not_found(char *str);
char	*init_empty(void);
char	*join_to_total(char *total, char *buffer);
char	*extract_line(char *total);
char	*save_rest(char *total);

#endif