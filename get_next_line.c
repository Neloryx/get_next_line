/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   get_next_line.c                                   :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: thdeglos <thdeglos@student.42lehavre.fr>  #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/11/09 17:21:15 by thdeglos         #+#    #+#              */
/*   Updated: 2026/11/15 13:28:51 by thdeglos        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_to_stash(int fd, char *stash, char *buf)
{
	int		ret;
	char	*tmp;

	ret = 1;
	while ((!stash || !ft_strchr(stash, '\n')) && ret > 0)
	{
		ret = read(fd, buf, BUFFER_SIZE);
		if (ret < 0)
		{
			free(stash);
			return (NULL);
		}
		buf[ret] = '\0';
		tmp = stash;
		stash = ft_strjoin(tmp, buf);
		free(tmp);
		if (!stash)
			return (NULL);
	}
	return (stash);
}

static char	*extract_line(char *stash)
{
	char	*nl;
	char	*line;
	size_t	len;

	nl = ft_strchr(stash, '\n');
	if (nl)
		len = (nl - stash) + 1;
	else
		len = ft_strlen(stash);
	line = malloc(len + 1);
	if (!line)
		return (NULL);
	ft_memcpy(line, stash, len);
	line[len] = '\0';
	return (line);
}

static char	*clean_stash(char *stash)
{
	char	*nl;
	char	*rest;
	size_t	len;

	nl = ft_strchr(stash, '\n');
	if (!nl || !nl[1])
	{
		free(stash);
		return (NULL);
	}
	len = ft_strlen(nl + 1);
	rest = malloc(len + 1);
	if (!rest)
	{
		free(stash);
		return (NULL);
	}
	ft_memcpy(rest, nl + 1, len);
	rest[len] = '\0';
	free(stash);
	return (rest);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;
	char		*buf;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	stash = read_to_stash(fd, stash, buf);
	free(buf);
	if (!stash || !stash[0])
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	line = extract_line(stash);
	stash = clean_stash(stash);
	return (line);
}
