/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 20:18:21 by jdupuis           #+#    #+#             */
/*   Updated: 2024/12/22 23:40:16 by jdupuis          ###   ########.fr       */
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

char	*get_next_line(int fd)
{
	char			*line;
	static char		buf[BUFFER_SIZE];
	size_t			r;
	int				nline_idx;

	line = malloc(BUFFER_SIZE * sizeof(char) + 1);
	if (!line)
		return (NULL);
	line[0] = '\0';
	if (buf[0] != '\0')
	{
		nline_idx = find_newline(buf);
		if (nline_idx != -1)
		{
			ft_memcpy(line, buf, nline_idx + 1);
			line[nline_idx + 1] = '\0';
			ft_memcpy(buf, buf + nline_idx + 1, BUFFER_SIZE - nline_idx - 1);
			return (buf[BUFFER_SIZE - nline_idx - 1] = '\0', line);
		}
		else
			line = ft_join(line, buf, BUFFER_SIZE);
	}
	r = read(fd, buf, BUFFER_SIZE);
	nline_idx = find_newline(buf);
	if (r <= 0 && buf[0] == 0)
		return (free(line), NULL);
	buf[r] = '\0';
	nline_idx = find_newline(buf);
	if (nline_idx != -1)
	{
		ft_memcpy(line + ft_strlen(line), buf, nline_idx +1);
		ft_memcpy(buf, buf + nline_idx + 1, r - nline_idx - 1);
		return (buf[r - nline_idx - 1] = '\0', line);
	}
	while (nline_idx == -1 && r == BUFFER_SIZE)
	{
		line = ft_join(line, buf, r);
		if (!line)
			return (NULL);
		r = read(fd, buf, BUFFER_SIZE);
		buf[r] = '\0';
		nline_idx = find_newline(buf);
		if (nline_idx != -1)
			line = ft_join(line, buf, nline_idx + 1);
	}
	if (r == 0 && nline_idx == -1)
	{
		line = ft_join(line, buf, r);
		if (!line)
			return (NULL);
		return (line);
	}
	if (r == 0 && buf[0] != 0)
		return (free(line), NULL);
	ft_memcpy(buf, buf + nline_idx + 1, r - nline_idx - 1);
	return (buf[r - nline_idx - 1] = '\0', line);
}
