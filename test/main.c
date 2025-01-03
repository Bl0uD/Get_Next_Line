/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 23:51:55 by jdupuis           #+#    #+#             */
/*   Updated: 2025/01/03 19:01:17 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int	main(int argc, char *argv[])
{
	int		fd;
	char	*line;

	if (argc != 2)
	{
		return (0);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		perror("Erreur d'ouverture de fichier");
		return (1);
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		write(1, line, ft_strlen(line));
		free(line);
	}
	close(fd);

	return (0);
}
