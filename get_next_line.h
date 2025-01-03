/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 20:21:18 by jdupuis           #+#    #+#             */
/*   Updated: 2025/01/03 18:56:54 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

int		find_newline(char *buf, int line_size);
int		ft_get_line(char **buf, int *line_size, char **l);
int		ft_read(char **buf, int *line_size, int fd);

char	*free_n_return(char **buf);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*get_next_line(int fd);

void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_realloc(void *ptr, size_t size, size_t new_size);

#endif
