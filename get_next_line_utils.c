/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 21:26:30 by jdupuis           #+#    #+#             */
/*   Updated: 2025/01/03 18:56:47 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	int		i;
	char	*str;

	if (!s)
		return (NULL);
	str = (char *)malloc(len + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (i < (int)len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

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

void	*ft_realloc(void *ptr, size_t size, size_t new_size)
{
	size_t		i;
	char		*new;

	new = malloc(new_size + 1);
	if (!new)
		return (NULL);
	i = 0;
	while (i < new_size + 1)
	{
		((char *)new)[i] = 0;
		i++;
	}
	i = 0;
	if (ptr)
	{
		while (i < size)
		{
			((char *)new)[i] = ((char *)ptr)[i];
			i++;
		}
		free(ptr);
	}
	((char *)new)[new_size] = '\0';
	return (new);
}
