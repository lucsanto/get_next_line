*This project has been created as part of the 42 curriculum by lucsanto*

<h1>Get Next Line</h1>

<p align="center">
  <img width="826" height="656" alt="image" src="https://github.com/user-attachments/assets/12ca2409-18d9-4d00-8fca-33dd28f4ae3a" />
</p>

<h2>Description</h2>

Get Next Line is a project from the 42 São Paulo curriculum. The goal of this project is to create a function that reads and returns one line at a time from a file descriptor.

This project reinforces very important concepts of C programming, such as file descriptors, static variables, dynamic memory allocation, buffer manipulation, string handling and memory leak prevention.

The function can be used to read text files, standard input and any valid file descriptor, returning each line individually with each function call.

<h3>Function Description</h3>

The project implements the following function:

```c
char	*get_next_line(int fd);
```

The function receives a file descriptor and returns the next line read from it.

The returned line includes the newline character `\n` when it exists. If the end of the file is reached and the last line does not end with a newline, the function returns the last line without `\n`.

When there is nothing else to read, or if an error occurs, the function returns `NULL`.

<h3>Project Files</h3>

The mandatory part contains:

<ul>
  <li>get_next_line.c</li>
  <li>get_next_line_utils.c</li>
  <li>get_next_line.h</li>
</ul>

The bonus part contains:

<ul>
  <li>get_next_line_bonus.c</li>
  <li>get_next_line_utils_bonus.c</li>
  <li>get_next_line_bonus.h</li>
</ul>

<h3>Mandatory Part</h3>

The mandatory version reads from one file descriptor and keeps track of what was read between function calls using a static variable.

The function does not read the whole file at once. It reads chunks of size `BUFFER_SIZE`, joins them to the saved content and stops reading as soon as a newline is found or when the end of the file is reached.

<h3>Bonus Part</h3>

The bonus version allows Get Next Line to manage multiple file descriptors at the same time.

This is done using only one static variable, but instead of a single pointer, the static variable is an array of pointers:

```c
static char	*total[MAX_FD];
```

Each file descriptor uses its own position in the array:

```c
total[fd]
```

This allows calls like this without mixing the reading state of each file:

```c
get_next_line(fd_a);
get_next_line(fd_b);
get_next_line(fd_a);
get_next_line(fd_b);
```

<h2>Algorithm Explanation</h2>

The algorithm is divided into three main steps.

<h3>1. Read until a newline is found</h3>

The function reads from the file descriptor using `read()`, with the size defined by `BUFFER_SIZE`.

The content read from the file is joined with the previous saved content. This saved content is necessary because one `read()` call can contain more than one line, or only part of a line.

The function keeps reading while no newline character is found and while the end of the file has not been reached.

<h3>2. Extract the current line</h3>

After reading enough content, the function extracts everything from the beginning of the saved string until the first `\n`.

If a newline is found, it is included in the returned string.

If no newline is found, the remaining content is returned as the last line.

<h3>3. Save the remaining content</h3>

After extracting the current line, the function saves everything that comes after the first `\n`.

This remaining content will be used in the next call to `get_next_line`.

If there is no remaining content, the saved pointer is freed and set to `NULL`.

<h3>Why this algorithm?</h3>

This approach was chosen because it respects the project requirement of reading as little as possible. The function does not read the entire file before returning lines. Instead, it stops reading as soon as it has enough content to return one complete line.

The static variable is essential because the function needs to remember unread content between calls.

<h2>Instructions</h2>

To compile the mandatory part with a buffer size of 42, run:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o gnl
```

Then run:

```bash
./gnl
```

To compile the bonus part, run:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line_bonus.c get_next_line_utils_bonus.c main.c -o gnl_bonus
```

The value of `BUFFER_SIZE` can be changed during compilation:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=1 get_next_line.c get_next_line_utils.c main.c -o gnl
```

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=9999 get_next_line.c get_next_line_utils.c main.c -o gnl
```

The project must also compile without explicitly passing `BUFFER_SIZE`, because the header defines a default value when it is not provided.

<h3>Example Usage</h3>

(it can be used to test my gnl)

```c
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line.h"

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("file.txt", O_RDONLY);
	if (fd < 0)
		return (1);
	line = get_next_line(fd);
	while (line)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}
```

If `file.txt` contains:

```txt
Hello
from
42
```

The output will be:

```txt
Hello
from
42
```

<h2>Testing</h2>

Some useful cases to test:

<ul>
  <li>Empty file</li>
  <li>File with only one line</li>
  <li>File with multiple lines</li>
  <li>File without newline at the end</li>
  <li>File with empty lines</li>
  <li>Very long line bigger than BUFFER_SIZE</li>
  <li>BUFFER_SIZE=1</li>
  <li>BUFFER_SIZE=42</li>
  <li>BUFFER_SIZE=9999</li>
  <li>Invalid file descriptor</li>
  <li>Standard input</li>
  <li>Multiple file descriptors for bonus</li>
</ul>

To test memory leaks, Valgrind can be used:

```bash
valgrind --leak-check=full --show-leak-kinds=all ./gnl
```

<h3>Simple Test Files</h3>

Create a normal file:

```bash
printf "line 1\nline 2\nline 3\n" > normal.txt
```

Create a file without newline at the end:

```bash
printf "first line\nsecond line\nlast line without newline" > no_newline.txt
```

Create a file with empty lines:

```bash
printf "\nline after empty\n\nend\n" > empty_lines.txt
```

Create an empty file:

```bash
touch empty.txt
```

<h2>Resources</h2>

<ul>
  <li>Obviously, the 42 Get Next Line subject, which I have a habit of creating some checklists with the help of Notion.</li>
  <li>Always my first and biggest source of information: man7.org, especially the documentation for read(), open() and file descriptors.</li>
  <li>I also used the C manual pages available in the terminal with commands like man read, man open and man malloc.</li>
  <li>I also had help from friends at 42, mainly to discuss the idea of static variables, file descriptors and edge cases.</li>
  <li>AI was used to organize this README and to help me with edge cases in my tests.</li>
</ul>

<h2>Personal Notes</h2>

The most important part of this project for me was understanding that the static variable is what allows the function to continue from where it stopped in the previous call.

Another important point was understanding that `read()` does not know what a line is. It only reads bytes. The responsibility of finding the line break, returning the correct line and saving the rest belongs to my own implementation.

For the bonus, the key idea was understanding that each file descriptor needs its own saved content. That is why the static variable becomes an array, where each position represents the saved content of one file descriptor.
