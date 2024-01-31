/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodralva <rodralva@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 15:18:54 by rodralva          #+#    #+#             */
/*   Updated: 2024/01/31 20:49:26 by rodralva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_keep_read(int fd, char *line, char *buff, char *extra)
{
	int	bytes;

	bytes = 1;
	while (bytes > 0 && ft_strchr(line, '\n') == 0)
	{
		bytes = read(fd, buff, BUFFER_SIZE);
		if (bytes < 0)
		{
			free (line);
			return (ft_free(buff, extra));
		}
		buff[bytes] = '\0';
		if (bytes != 0)
			line = ft_strjoin(line, buff);
		if (!line)
			return (ft_free(buff, extra));
	}
	free (buff);
	free (extra);
	return (line);
}

char	*ft_line(char *buff)
{
	char	*ret;
	int		i;
	int		l;

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

char	*ft_read(int fd, char *extra, char *line)
{
	char	*buff;

	if (ft_strchr(line, '\n') != 0)
	{
		free (extra);
		return (line);
	}
	buff = ft_calloc(BUFFER_SIZE + 1, 1);
	if (!buff)
		return (NULL);
	return (ft_keep_read(fd, line, buff, extra));
}

char	*ft_extra(char *buff)
{
	char	*ret;
	int		i;
	int		j;

	i = 0;
	j = 0;
	ret = ft_calloc(1, 1);
	if (!buff)
		return (NULL);
	while (buff[i] && buff[i] != '\n')
		i++;
	if (buff[i])
		i++;
	ret = ft_strjoin(ret, buff + i);
	free(buff);
	buff = NULL;
	return (ret);
}

char	*get_next_line(int fd)
{
	static char	*buff = NULL;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = ft_calloc(1, 1);
	if (!line)
		return (NULL);
	line = ft_strjoin(line, buff);
	buff = ft_read(fd, buff, line);
	if (!buff || !*buff)
	{
		free (buff);
		buff = NULL;
		return (NULL);
	}
	line = ft_line(buff);
	buff = ft_extra(buff);
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
