/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_test.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 20:18:21 by jdupuis           #+#    #+#             */
/*   Updated: 2024/12/22 23:34:53 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*psrc;
	char	*pdest;

	i = 0;
	psrc = (char *)src;
	pdest = (char *)dest;
	if (psrc == NULL && pdest == NULL)
		return (dest);
	while (i < n)
	{
		pdest[i] = psrc[i];
		i++;
	}
	return (pdest);
}

char	*ft_join(char *original, const char *addition, size_t r)
{
	size_t	original_len;
	char	*new_str;

	original_len = ft_strlen(original);
	new_str = malloc(original_len + r + 1);
	if (!new_str)
		return (NULL);
	ft_memcpy(new_str, original, original_len);
	ft_memcpy(new_str + original_len, addition, r);
	new_str[original_len + r] = '\0';
	free(original);
	return (new_str);
}

char	*initialize_line(void)
{
	char	*line;

	line = malloc(BUFFER_SIZE * sizeof(char) + 1);
	if (!line)
		return (NULL);
	line[0] = '\0';
	return (line);
}

char	*process_existing_buffer(char *line, char *buf)
{
	int	newline_idx;

	newline_idx = find_newline(buf);
	if (newline_idx != -1)
	{
		ft_memcpy(line, buf, newline_idx + 1);
		line[newline_idx + 1] = '\0';
		ft_memcpy(buf, buf + newline_idx + 1, BUFFER_SIZE - newline_idx - 1);
		buf[BUFFER_SIZE - newline_idx - 1] = '\0';
		return (line);
	}
	else
		return (ft_join(line, buf, BUFFER_SIZE));
}

char	*read_and_process(int fd, char *line, char *buf)
{
	size_t	r;
	int		newline_idx;

	r = read(fd, buf, BUFFER_SIZE);
	if (r <= 0 && buf[0] == 0)
		return (free(line), NULL);
	buf[r] = '\0';
	newline_idx = find_newline(buf);
	if (newline_idx != -1)
	{
		ft_memcpy(line + ft_strlen(line), buf, newline_idx + 1);
		ft_memcpy(buf, buf + newline_idx + 1, r - newline_idx - 1);
		buf[r - newline_idx - 1] = '\0';
		return (line);
	}
	while (r == BUFFER_SIZE)
	{
		line = ft_join(line, buf, r);
		if (!line)
			return (NULL);
		r = read(fd, buf, BUFFER_SIZE);
		buf[r] = '\0';
		newline_idx = find_newline(buf);
		if (newline_idx != -1)
			return (ft_join(line, buf, newline_idx + 1));
	}
	return (ft_join(line, buf, r));
}

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE];
	char		*line;

	line = initialize_line();
	if (!line)
		return (NULL);
	if (buf[0] != '\0')
	{
		line = process_existing_buffer(line, buf);
		if (line && find_newline(buf) != -1)
			return (line);
	}
	return (read_and_process(fd, line, buf));
}
