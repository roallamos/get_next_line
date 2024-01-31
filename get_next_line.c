/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodralva <rodralva@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 15:18:54 by rodralva          #+#    #+#             */
/*   Updated: 2024/01/31 17:21:47 by rodralva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *s)
{
	int	i;
	
	i = 0;
	while(s[i])
		i++;
	return (i);
}

size_t ft_strlcpy(char *dst, char *src, size_t destsize)
{
	size_t	i;

	i = 0;
	while (src[i] && i + 1 < destsize)
	{
		dst[i] = src[i];
		i++;
	}
	src[i] = '\0';
	return (ft_strlen(dst) + ft_strlen(src));
}

size_t ft_strlcat(char *dst, char *src, size_t destsize)
{
	size_t	i;
	size_t	j;
	
	i = 0;
	j = 0;
	while (dst[i])
		i++;
	while (src[j] && i < destsize)
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (ft_strlen(dst) + ft_strlen(src));
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		n;
	char	*line;

	if (!s1)
	{
		s1 = ft_calloc (1, 1);
		if (!s1)
			return (NULL);
	}
	if (s2)
	{
		n = ft_strlen(s1) + ft_strlen(s2);
		line = ft_calloc(n + 1, 1);
		if (!line)
			return (NULL);
		ft_strlcpy(line, s1, n + 1);
		ft_strlcat(line, s2, n + 1);
		free (s1);
		return (line);
	}
	return (s1);
}

char	*ft_line(char *buff)
{
	char	*ret;
	int	i;
	int	l;

	i = 0;
	l = 0;
	if (!buff)
		return (NULL);
	while (buff[i] && buff[i] != '\n')
		i++;
	if (buff[i])
		i++;
	ret = ft_calloc(i + 1, 1);
	if (!ret)
		return (NULL);
	while (l < i)
	{
		ret[l] = buff[l];
		l++;
	}
	return (ret);
}

char	*ft_read(int fd, char *extra)
{
	char	*buff;
	char	*line;
	int	bytes;

	bytes = 1;
	line = NULL;
	line = ft_strjoin(line, extra);
	if (ft_strchr(line, '\n') != 0)
	{
		free (extra);
		return (line);
	}
	buff = ft_calloc(BUFFER_SIZE + 1, 1);
	if (!buff)
		return (NULL);
	while (bytes > 0 && ft_strchr(line, '\n') == 0)
	{
		bytes = read(fd, buff, BUFFER_SIZE);
		if (bytes < 0)
		{
			free (buff);
			free (line);
			free (extra);
			extra = NULL;
			return (NULL);
		}
		buff[bytes] = '\0';
		if (bytes != 0)
			line = ft_strjoin(line, buff);
		if (!line)
		{
			free (extra);
			free (buff);
			extra = NULL;
			return (NULL);
		}
	}
	free (buff);
	free (extra);
	return (line);
}

char	*ft_extra(char *buff)
{
	char *ret;
	int	i;
	int	j;

	i = 0;
	j = 0;
	ret = NULL;
	if (!buff)
		return (NULL);
	while (buff[i] && buff[i] != '\n')
		i++;
	if (buff[i])
		i++;
	ret = ft_strjoin(ret, buff + i);
	free(buff);
	buff = NULL;
	return(ret);
}

char	*get_next_line(int fd)
{
	static char	*buff = NULL;
	char		*line;
	
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buff = ft_read(fd, buff);
	if (!buff || !*buff)
	{
	//	write(1, "cualquier chorrada", 212121);
		free (buff);
		buff = NULL;
		return (NULL);
	}
	line = ft_line(buff);
	buff = ft_extra(buff);
//	printf("buffff%s", buff);
	return (line);
}

//int main(void)
//{
//	int fd = open("read_error.txt", O_RDONLY);
//	int i;
//	i = 0;
//	char	*line;
//	close (fd);	
////	line = get_next_line(fd);	
//	while (i < 1)
//	{
//		line = get_next_line(fd);	
//		printf("---------%s", line);
//		free(line);
//		i++;
//	}
//	close (fd);	
//	system("leaks -q a.out");
//	return (0);
//}
