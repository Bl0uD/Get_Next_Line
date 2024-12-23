/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 23:51:55 by jdupuis           #+#    #+#             */
/*   Updated: 2024/12/22 23:51:58 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../get_next_line.h"

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
