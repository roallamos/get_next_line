/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodralva <rodralva@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 19:16:21 by rodralva          #+#    #+#             */
/*   Updated: 2024/01/28 14:35:05 by rodralva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_memset(void *buf, int c, size_t len)
{
	size_t			i;
	unsigned char	*t;

	i = 0;
	t = (unsigned char *) buf;
	while (i < len)
	{
		t[i] = c;
		i++;
	}
	return (t);
}

void	*ft_calloc(size_t count, size_t size)
{
	char	*array;

	if (size != 0 && count > SIZE_MAX / size)
		return (NULL);
	array = (char *) malloc(count * size);
	if (array == NULL)
		return (NULL);
	ft_memset(array, 0, (count * size));
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
