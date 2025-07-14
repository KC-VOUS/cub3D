/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsingh <fsingh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 18:26:12 by sdakhlao          #+#    #+#             */
/*   Updated: 2025/07/14 11:42:14 by fsingh           ###   ########.fr       */
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

int		ft_flood_fill(char **map, int y, int x)
{
	if (x < 0 || map[y] == NULL || y < 0 || map[y][x] == '\0')
		return (0);
	if (map[y][x] == ' ')
		return (0);
	if (map[y][x] != '0')
		return (1);
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

int		start_parse_map(char **cub, int y, int x)
{
	char	**map;
	int		res;
	(void)x;
	(void)y;

	res = 0;
	map = dup_map(cub);
	if (!map)
		return (0);
	res = ft_flood_fill(map, y, x);
	free_tab(map);
	printf("res = %d\n", res);
	return (res);
}

int		check_map(char **cub)
{
	int	i;
	int	j;

	i = 0;
	while (cub[i])
	{
		j = 0;
		if (cub[i][0] == '1' || cub[i][0] == ' ')
		{
			while (cub[i][j] != '0' && cub[i][j] != '\n')
				j++;
			if (cub[i][j] == '0')
				return (start_parse_map(cub, i, j));
		}
		i++;
	}
	return (0);
}
