#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"

/* Usage : ./test file [file ...]   (without arguments : reads stdin) */

static void	read_all(int fd, const char *name)
{
	char	*line;
	int		n;

	printf("=== %s (fd %d) ===\n", name, fd);
	n = 1;
	while ((line = get_next_line(fd)))
	{
		printf("[%02d] \"", n++);
		for (int i = 0; line[i]; i++)
		{
			if (line[i] == '\n')
				printf("\\n");
			else
				putchar(line[i]);
		}
		printf("\"\n");
		free(line);
	}
	printf("--> end (NULL) after %d line(s)\n\n", n - 1);
}

int	main(int ac, char **av)
{
	int	fd;

	if (ac == 1)
		read_all(0, "stdin");
	for (int i = 1; i < ac; i++)
	{
		fd = open(av[i], O_RDONLY);
		if (fd < 0)
		{
			perror(av[i]);
			continue ;
		}
		read_all(fd, av[i]);
		close(fd);
	}
	printf("=== invalid fds (must return NULL) ===\n");
	printf("fd -1   : %s\n", get_next_line(-1) ? "ERROR" : "NULL ok");
	printf("fd 42   : %s\n", get_next_line(42) ? "ERROR" : "NULL ok");
	return (0);
}
