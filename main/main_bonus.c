/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdeglos <thdeglos@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/15 13:41:11 by thdeglos          #+#    #+#             */
/*   Updated: 2026/11/15 13:41:16 by thdeglos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "get_next_line_bonus.h"

/* Usage : ./test_bonus f1 f2 f3 ...  -> reads alternating (round-robin) */

#define MAX 16

static void	print_line(int idx, int fd, char *line)
{
	printf("fd %d (%s) : \"", fd, idx % 2 ? "impair" : "pair");
	for (int i = 0; line[i]; i++)
	{
		if (line[i] == '\n')
			printf("\\n");
		else
			putchar(line[i]);
	}
	printf("\"\n");
}

int	main(int ac, char **av)
{
	int		fds[MAX];
	int		done[MAX];
	int		nb;
	int		left;
	char	*line;

	nb = 0;
	for (int i = 1; i < ac && nb < MAX; i++)
	{
		fds[nb] = open(av[i], O_RDONLY);
		if (fds[nb] < 0)
		{
			perror(av[i]);
			continue ;
		}
		printf("%s -> fd %d\n", av[i], fds[nb]);
		done[nb++] = 0;
	}
	printf("\n--- alternating read ---\n");
	left = nb;
	while (left > 0)
	{
		for (int i = 0; i < nb; i++)
		{
			if (done[i])
				continue ;
			line = get_next_line(fds[i]);
			if (!line)
			{
				printf("fd %d : NULL (done)\n", fds[i]);
				done[i] = 1;
				left--;
				continue ;
			}
			print_line(i, fds[i], line);
			free(line);
		}
	}
	for (int i = 0; i < nb; i++)
		close(fds[i]);
	return (0);
}
