/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsingh <fsingh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 18:25:30 by sdakhlao          #+#    #+#             */
/*   Updated: 2025/07/28 16:55:00 by fsingh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	valid_extension(char *file)
{
	int	i;

	i = 0;
	while (file[i])
		i++;
	if (i < 5 || strcmp(file + i - 4, ".cub"))
	{
		write(2, "Error: Wrong file extension\n", 29);
		exit(EXIT_FAILURE);
	}
}

char	**malloc_tab(char *file)
{
	int		fd;
	int		i;
	char	*line;
	char	**tab;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		free(line);
		i++;
		line = get_next_line(fd);
	}
	close(fd);
	tab = malloc(sizeof(char *) * (i + 1));
	if (!tab)
		exit(EXIT_FAILURE);
	return (tab);
}

void	cp_file(char	*file, t_details *details)
{
	int		i;
	int		fd;
	char	*line;
	char	**tab;

	valid_extension(file);
	tab = malloc_tab(file);
	i = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	line = get_next_line(fd);
	while (line)
	{
		tab[i++] = line;
		line = get_next_line(fd);
	}
	tab[i] = NULL;
	close(fd);
	check_data(tab);
	init_struct(details);
	fill_details(details, tab);
	print_tab(tab);
	free_tab(tab);
}
