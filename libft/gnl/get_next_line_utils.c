/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneto-de <nneto-de@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 17:19:17 by nneto-de          #+#    #+#             */
/*   Updated: 2024/01/23 19:47:27 by nneto-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	gnl_strclen(const char *str, int c)
{
	int	len;

	len = 0;
	if (!str)
		return (0);
	while (str[len] != '\0' && str[len] != c)
	{
		len++;
	}
	return (len);
}

char	*gnl_strchr(const char *str, int c)
{
	int		i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == c)
		{
			return ((char *)(str + i));
		}
		i++;
	}
	return (NULL);
}

void	*gnl_memcpy(void *dest, const void *src, size_t n)
{
	size_t		i;
	char		*s;
	char		*d;

	i = 0;
	s = (char *)src;
	d = (char *)dest;
	if ((dest == NULL) && (src == NULL))
		return (NULL);
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}

char	*gnl_merge_strs(char *s1, char const *s2)
{
	size_t	len_1;
	size_t	len_2;
	char	*merged;

	len_1 = 0;
	if (s1)
		len_1 = gnl_strclen(s1, '\0');
	len_2 = gnl_strclen(s2, '\0');
	merged = (char *)malloc(sizeof(char) * (len_1 + len_2 + 1));
	if (!merged)
		return (NULL);
	if (s1)
		gnl_memcpy(merged, s1, len_1);
	gnl_memcpy(merged + len_1, s2, len_2);
	merged[len_1 + len_2] = '\0';
	if (s1)
		free(s1);
	return (merged);
}

char	*gnl_dupstr(const char *s, size_t n)
{
	char	*dup;
	size_t	i;

	i = 0;
	dup = (char *)malloc(n + 1);
	if (!dup)
		return (NULL);
	while (s[i] && i < n)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
