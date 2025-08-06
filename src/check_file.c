/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdakhlao <sdakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 19:18:17 by sdakhlao          #+#    #+#             */
/*   Updated: 2025/08/03 23:36:06 by sdakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	check_elements(char **cub)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (cub[i])
	{
		if (!strncmp(cub[i], "NO", 2))
			count += 1;
		else if (!strncmp(cub[i], "SO", 2))
			count += 10;
		else if (!strncmp(cub[i], "WE", 2))
			count += 100;
		else if (!strncmp(cub[i], "EA", 2))
			count += 1000;
		else if (!strncmp(cub[i], "F", 1))
			count += 10000;
		else if (!strncmp(cub[i], "C", 1))
			count += 100000;
		i++;
	}
	if (count == 111111)
		return (1);
	else
		return (0);
}

int	check_order(char **cub)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cub[i])
		i++;
	i -= 1;
	while (cub[i][j] == ' ')
		j++;
	if (cub[i][j] != '1')
	{
		printf("Error: la map doit etre en dernier\n");
		return (free_tab(cub), 0);
	}
	if (!check_elements(cub))
	{
		printf("Error: mauvais nombre d'elements\n");
		return (free_tab(cub), 0);
	}
	return (1);
}

void	check_data(char **cub)
{
	if (!check_order(cub))
		exit(EXIT_FAILURE);
	if (!check_texture(cub))
		exit(EXIT_FAILURE);
	if (!check_color(cub))
		exit(EXIT_FAILURE);
	if (!check_map(cub))
	{
		free_tab(cub);
		exit(EXIT_FAILURE);
	}
	if (!check_map_content(cub))
	{
		free_tab(cub);
		exit(EXIT_FAILURE);
	}
}
