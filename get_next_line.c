/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodralva <rodralva@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 15:18:54 by rodralva          #+#    #+#             */
/*   Updated: 2024/01/28 14:35:02 by rodralva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_static(char	*stc, char *buff)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (buff[i] && buff[i] != '\n')
		i++;
	if (buff[i])
		i++;
	while (buff[i + j])
		j++;
	stc = ft_calloc(i + j + 1, 1);
	if (!stc)
		return (NULL);
	j = 0;
	while(buff[i + j])
	{
		stc[j] = buff[i + j];
		j++;
	}
	return (stc);
}

char	*ft_join(char *s1, char *s2)
{
	int 	i;
	int 	j;
	int		n;
	char	*line;

	i = 0;
	j = 0;

	if (!*s1)
		s1 = ft_calloc (1, 1);
	if (!*s2)
		return (NULL);
	while (s1[i])
		i++;
	while (s2[j] && s2[j] != '\n')
		j++;
	if (s2[j] == '\n')
		j++;
//	printf("buffff %s\n", s2);
//	printf("lineee %s\n", s1);
//	printf("iiii %d jjjj %d\n", i, j);
	line = ft_calloc(i + j + 1, 1);
	if (!line)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		line[i] = s1[i];
		i++;
	}
	n = 0;
	while (s2[n] && n < j)
	{
		line[i + n] = s2[n];
		n++;
	}
	free (s1);
	return (line);
}

char	*ft_read(char *buff, char *stc, int fd)
{
	char	*line;
	int		bytes;

	bytes = 1;
	line = ft_calloc(1, 1);
	if (!line)
		return (NULL);
	if (stc && *stc)
	{
		line = ft_join(line, stc);
		if (!line)
			return (NULL);
		if (ft_strchr(line, '\n') != 0)
			return (line);// falta aqui cambiar a estatica cando ten recollida mais de linea e mmedia do texto
	}
	while (bytes > 0 && ft_strchr(line, '\n') == 0)
	{
		bytes = read(fd, buff, BUFFER_SIZE);
		if (bytes < 0)
		{
			free (buff);
			return (NULL);
		}

		line = ft_join(line, buff);
	}
	stc = ft_static(stc, buff);
//	printf("stccccc %s\n", stc);
	return (line);
}


char	*get_next_line(int fd)
{
	static char	*stc;
	char		*line;
	char		*buff;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buff = ft_calloc(BUFFER_SIZE + 1, 1);
	if (!buff)
		return (NULL);
	line = ft_read(buff, stc, fd);
	if (!line)
		return (NULL);
	if (*buff)
		stc = ft_static(stc, buff);
	else
	{
		while (*stc && *stc != '\n')
			stc++;
		if (*stc)
			stc++;
	}
	free (buff);
	return (line);
}

int main(void)
{
	int fd = open("chistes.txt", O_RDONLY);
	int i;
	i = 0;
	char	*line;
	line = get_next_line(fd);	
	while (i < 100)
	{
		printf("---------%s", line);
		free(line);
		line = get_next_line(fd);	
		i++;
	}
	close (fd);
	system("leaks -q a.out");
	return (0);
}
