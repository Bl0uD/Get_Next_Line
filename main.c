/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 23:20:52 by jdupuis           #+#    #+#             */
/*   Updated: 2024/12/24 17:25:41 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	main(void)
{

	int fd = open("test_gnl", O_RDONLY);
	if (fd == -1)
	{
		perror("Erreur d'ouverture du fichier");
		return (1);
	}

	char *line;

	while ((line = get_next_line(fd)) != NULL) {
		printf("Ligne lue: %s", line);
		free(line);
	}

	close(fd);
	return (0);
}
