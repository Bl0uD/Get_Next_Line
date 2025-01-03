/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 20:18:21 by jdupuis           #+#    #+#             */
/*   Updated: 2025/01/03 18:55:43 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_read(char **buf, int *line_size, int fd)
	{
	int		bytes_read;
	char	*temp;

	temp = ft_realloc(*buf, *line_size, *line_size + BUFFER_SIZE);
	if (!temp)
	{
		free(*buf);
		*buf = NULL;
		*line_size = 0;
		return (-1);
	}
	*buf = temp;
	bytes_read = read(fd, *buf + *line_size, BUFFER_SIZE);
	if (bytes_read < 0)
	{
		free(*buf);
		*buf = NULL;
		*line_size = 0;
		return (-1);
	}
	if (bytes_read > 0)
		*line_size += bytes_read;
	(*buf)[*line_size] = '\0';
	return (bytes_read);
}

int	find_newline(char *buf, int line_size)
{
	int	newline_idx;

	if (!buf)
		return (-1);
	newline_idx = 0;
	while (buf[newline_idx] && newline_idx < line_size)
	{
		if (buf[newline_idx] == '\n')
			return (newline_idx);
		newline_idx++;
	}
	return (-1);
}

int	ft_get_line(char **buf, int *line_size, char **line)
{
	int		newline_idx;

	newline_idx = find_newline(*buf, *line_size);
	if (newline_idx == -1)
		return (0);
	*line = ft_substr(*buf, 0, newline_idx + 1);
	ft_memcpy(*buf, *buf + newline_idx + 1, *line_size - newline_idx - 1);
	*line_size -= newline_idx + 1;
	return (1);
}

char	*free_n_return(char **buf)
{
	free(*buf);
	*buf = NULL;
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*buf;
	static int	line_size;
	int			bytes_read;
	char		*line;

	if (fd < 0)
		return (free_n_return(&buf));
	if (ft_get_line(&buf, &line_size, &line) == 1)
		return (line);
	while (1)
	{
		bytes_read = ft_read(&buf, &line_size, fd);
		if (bytes_read == -1 || (bytes_read == 0 && line_size == 0))
			return (free_n_return(&buf));
		if (bytes_read == 0 && line_size > 0)
		{
			line = ft_substr(buf, 0, line_size);
			line_size = 0;
			free_n_return(&buf);
			return (line);
		}
		if (ft_get_line(&buf, &line_size, &line) == 1)
			return (line);
	}
}
