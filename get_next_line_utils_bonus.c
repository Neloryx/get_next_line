/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   get_next_line_utils.c                             :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: thdeglos <thdeglos@student.42lehavre.fr>  #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/11/09 17:21:11 by thdeglos         #+#    #+#              */
/*   Updated: 2026/11/09 19:08:40 by thdeglos        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s != (char) c)
	{
		if (!*s)
			return (NULL);
		s++;
	}
	return ((char *) s);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;
	size_t				i;

	if (!dest && !src)
		return (NULL);
	d = (unsigned char *) dest;
	s = (const unsigned char *) src;
	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*nstring;
	size_t	lens1;
	size_t	lens2;

	if (!s2)
		return (NULL);
	lens1 = 0;
	if (s1)
		lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	nstring = malloc(lens1 + lens2 + 1);
	if (!nstring)
		return (NULL);
	ft_memcpy(nstring, s1, lens1);
	ft_memcpy(nstring + lens1, s2, lens2);
	nstring[lens1 + lens2] = '\0';
	return (nstring);
}
