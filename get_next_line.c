/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 20:18:21 by jdupuis           #+#    #+#             */
/*   Updated: 2024/12/21 19:56:13 by jdupuis          ###   ########.fr       */
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

char	*ft_join(char *original, const char *addition)
{
	size_t	original_len = ft_strlen(original);
	size_t	addition_len = ft_strlen(addition);
	char	*new_str;

	new_str = malloc(original_len + addition_len + 1);
	if (!new_str)
		return NULL;
	ft_memcpy(new_str, original, original_len);
	ft_memcpy(new_str + original_len, addition, addition_len);
	free(original);
	return (new_str);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*buf;
	size_t		r;
	size_t		new_line_idx;

	if (buf == 0)
		buf = malloc(BUFFER_SIZE * sizeof(char));
	r = read(fd, buf, BUFFER_SIZE);
printf("r : %zu\n", r);
printf("buf : %s\n", buf);
	new_line_idx = return_to_line(buf);
printf("new_line_idx : %zu\n", new_line_idx);
	if (new_line_idx != -1)
	{
		line = malloc(new_line_idx * sizeof(char) + 1);
		ft_memcpy(line, buf, new_line_idx);
		line[new_line_idx] = '\0';
		ft_memcpy(buf, buf + new_line_idx + 1, r - new_line_idx);
		return (line);
	}
	line = ft_strndup(buf, r - new_line_idx);
	while (return_to_line(buf) == -1)
	{
		r = read(fd, buf, BUFFER_SIZE);
		ft_join(line, buf);
		ft_memcpy(buf, buf + new_line_idx + 1, r - new_line_idx);
	}
	return (line);
}

int main()
{
    int fd;
    char *line;

    // Ouvre un fichier de test (remplacez "test.txt" par un fichier réel si nécessaire)
    fd = open("test.txt", O_RDONLY);
    if (fd == -1)
    {
        perror("Erreur d'ouverture de fichier");
        return 1;
    }

    // Test de lecture ligne par ligne
    printf("Lecture ligne par ligne à partir de 'test.txt':\n");
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("Ligne lue: %s", line); // Affiche la ligne
        free(line); // Libère la mémoire allouée pour chaque ligne lue
    }

    // Ferme le fichier
    close(fd);

    return 0;
}