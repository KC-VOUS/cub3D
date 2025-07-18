/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsingh <fsingh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 18:26:12 by sdakhlao          #+#    #+#             */
/*   Updated: 2025/07/16 18:00:17 by fsingh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

char	**dup_map(char **cub)
{
	char	**dup;
	int		i;

	i = 0;
	while (cub[i])
		i++;
	dup = malloc(sizeof(char *) * (i + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (cub[i])
	{
		dup[i] = ft_strdup(cub[i]);
		if (!dup[i])
		{
			free_tab(dup);
			return (NULL);
		}
		i++;
	}
	dup[i] = NULL;
	return (dup);
}

int	ft_flood_fill(char **map, int y, int x)
{
	if (y < 0 || map[y] == NULL || x < 0 || map[y][x] == '\0')
		return (1);
	if (map[y][x] == ' ' || map[y][x] == '\n')
		return (0);
	if (map[y][x] == 'X' || map[y][x] == '1')
		return (1);
	if (map[y][x] != '0' && map[y][x] != 'N' && map[y][x] != 'S'
		&& map[y][x] != 'E' && map[y][x] != 'O')
		return (printf("Invalid caracter in map : '%c'\n", map[y][x]), 0);
	map[y][x] = 'X';
	if (!ft_flood_fill(map, y + 1, x))
		return (0);
	if (!ft_flood_fill(map, y - 1, x))
		return (0);
	if (!ft_flood_fill(map, y, x + 1))
		return (0);
	if (!ft_flood_fill(map, y, x - 1))
		return (0);
	return (1);
}

int	start_parse_map(char **cub, int y, int x)
{
	char	**map;
	int		res;

	res = 0;
	map = dup_map(cub);
	if (!map)
		return (0);
	res = ft_flood_fill(map, y, x);
	free_tab(map);
	return (res);
}

int	check_map(char **cub)
{
	int	i;
	int	j;

	i = 0;
	while (cub[i] && cub[i][0] != ' ' && cub[i][0] != '1')
		i++;
	while (cub[i])
	{
		j = 0;
		while (cub[i][j])
		{
			if (cub[i][j] == 'N' || cub[i][j] == 'S'
				|| cub[i][j] == 'O' || cub[i][j] == 'E')
			{
				if (!start_parse_map(cub, i, j))
					return (printf("Map invalid\n"), free_tab(cub), 0);
				else
					return (1);
			}
			j++;
		}
		i++;
	}
	return (printf("Map invalid\n"), 0);
}
