/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodralva <rodralva@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 19:16:21 by rodralva          #+#    #+#             */
/*   Updated: 2024/01/31 20:49:30 by rodralva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_free(char *buff, char *extra)
{
	free (buff);
	free (extra);
	extra = NULL;
	return (NULL);
}

void	ft_strlcpycat(char *dst, char *src, size_t destsize, int f)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (f == 0)
	{
		while (src[i] && i + 1 < destsize)
		{
			dst[i] = src[i];
			i++;
		}
	}
	else
	{
		j = 0;
		while (dst[i])
			i++;
		while (src[j] && i < destsize)
		{
			dst[i] = src[j];
			i++;
			j++;
		}
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	char	*array;
	size_t	i;

	i = 0;
	if (size != 0 && count > SIZE_MAX / size)
		return (NULL);
	array = (char *) malloc(count * size);
	if (array == NULL)
		return (NULL);
	while (i < count * size)
	{
		array[i] = '\0';
		i++;
	}
	return (array);
}

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*t;

	i = 0;
	t = (char *) s;
	if (!s)
		return (NULL);
	while (t[i])
	{
		if (t[i] == (char) c)
			return (&t[i]);
		i++;
	}
	if (!(char) c)
		return (&t[i]);
	return (0);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	j = 0;
	if (s2)
	{
		while (s1[i])
			i++;
		while (s2[j])
			j++;
		line = ft_calloc(i + j + 1, 1);
		if (!line)
			return (NULL);
		ft_strlcpycat(line, s1, i + j + 1, 0);
		ft_strlcpycat(line, s2, i + j + 1, 1);
		free (s1);
		return (line);
	}
	return (s1);
}
