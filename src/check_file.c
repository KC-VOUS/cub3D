/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsingh <fsingh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 19:18:17 by sdakhlao          #+#    #+#             */
/*   Updated: 2025/08/18 20:34:28 by fsingh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

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
		printf("la map doit etre en dernier\n");
		return (free_tab(cub), 0);
	}
	return (1);
}

int	check_number(char *color)
{
	int	i;

	i = 0;
	while (color[i] == ' ')
		i++;
	while (color[i] >= '0' && color[i] <= '9')
		i++;
	while (color[i] && (color[i] == ' ' || color[i] == '\n'))
		i++;
	if (!color[i])
		return (1);
	else
		return (0);
}

int	check_c(char **color)
{
	int	i;

	i = 0;
	while (color[i])
		i++;
	if (i > 3)
	{
		printf("Error: mauvais format rgb\n");
		free_tab(color);
		return (0);
	}
	i = 0;
	while (color[i])
	{
		if (ft_atoi(color[i]) < 0 || ft_atoi(color[i]) > 255
			|| !check_number(color[i]))
		{
			printf("Error: range rgb non respecte\n");
			free_tab(color);
			return (0);
		}
		i++;
	}
	free_tab(color);
	return (1);
}

int	check_color(char **cub)
{
	int		i;
	char	**tab;

	i = 0;
	tab = NULL;
	while (cub[i])
	{
		if (!strncmp(cub[i], "F", 1) || !strncmp(cub[i], "C", 1))
		{
			tab = ft_split(cub[i] + 1, ',');
			if (!check_c(tab))
			{
				free_tab(cub);
				return (0);
			}
		}
		i++;
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
	 	exit(EXIT_FAILURE);
	if (!check_map_content(cub))
		exit(EXIT_FAILURE);
}
