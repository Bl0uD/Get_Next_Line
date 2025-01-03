/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 20:18:21 by jdupuis           #+#    #+#             */
/*   Updated: 2024/12/26 16:19:38 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	while (n--)
		*ptr++ = 0;
}

char	*get_next_line(int fd)
{
	char			*line;
	static char		buf[BUFFER_SIZE] = {0};
	static size_t	buf_size = 0;
	ssize_t			r;
	int				nline_idx;
	int				line_size;

	nline_idx = find_newline(buf, buf_size);
	if (nline_idx != -1)
	{
		line = malloc(sizeof(char) * (nline_idx + 2));
		if (line == NULL)
			return (NULL);
		ft_memcpy(line, buf, nline_idx + 1);
		ft_memcpy(buf, buf + nline_idx + 1, buf_size - nline_idx - 1);
		ft_bzero(buf + buf_size - nline_idx - 1, BUFFER_SIZE - buf_size + 1);
		buf_size = buf_size - nline_idx - 1;
		line[nline_idx + 1] = '\0';
		return (line);
	}
	line = malloc(sizeof(char) * (buf_size));
	if (buf_size != 0 && line == NULL)
		return (NULL);
	ft_memcpy(line, buf, buf_size);
	line_size = buf_size;
	do
	{
		r = read(fd, buf, BUFFER_SIZE);
		if (r == -1)
		{
			free (line);
			return (NULL);
		}
		buf_size = r;
		nline_idx = find_newline(buf, buf_size);
		if (nline_idx != -1 && buf_size == BUFFER_SIZE)
		{
			line = ft_join(line, line_size, buf, nline_idx + 1);
			if (!line)
				return (NULL);
			line_size += nline_idx + 1;
			ft_memcpy(buf, buf + nline_idx + 1, BUFFER_SIZE - nline_idx - 1);
			ft_bzero(buf + (BUFFER_SIZE - nline_idx - 1), buf_size - nline_idx);
			buf_size = BUFFER_SIZE - nline_idx - 1;
			line[line_size] = '\0';
			return (line);
		}
		else if (nline_idx != -1 && buf_size > 0)
		{
			line = ft_join(line, line_size, buf, nline_idx + 1);
			if (!line)
				return (NULL);
			line_size += nline_idx + 1;
			ft_memcpy(buf, buf + nline_idx + 1, buf_size - nline_idx - 1);
			ft_bzero(buf + (buf_size - nline_idx - 1), nline_idx + 1);
			buf_size -= nline_idx - 1;
			line[line_size] = '\0';
			return (line);
		}
		else if (buf_size != 0 && buf_size != BUFFER_SIZE && nline_idx == -1)
		{
			line = ft_join(line, line_size, buf, buf_size);
			if (!line)
				return (NULL);
			line[buf_size + line_size] = '\0';
			buf_size = 0;
			return (line);
		}
		else if (buf_size == 0 && line[0] == 0)
		{
			free (line);
			return (NULL);
		}
		line = ft_join(line, line_size, buf, buf_size);
		line_size += buf_size;
		if (!line)
			return (NULL);
	}
	while (nline_idx == -1 && buf_size != 0);
	line[line_size] = '\0';
	return (line);
}
