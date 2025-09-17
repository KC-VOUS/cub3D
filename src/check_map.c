/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdakhlao <sdakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 18:26:12 by sdakhlao          #+#    #+#             */
/*   Updated: 2025/09/17 19:10:36 by sdakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	check_islands(char **cub)
{
	int	j;
	int	i;

	i = first_line_detector(cub);
	while (cub[i])
	{
		j = 0;
		while (cub[i][j])
		{
			if (cub[i][j] == '0')
			{
				if (!(cub[i][j - 1]) || !(cub[i][j + 1]))
					return (0);
				else if ((cub[i][j - 1] == ' ') || (cub[i][j + 1] == ' ')
					|| (cub[i][j - 1] == '\n') || (cub[i][j + 1] == '\n'))
					return (0);
				j++;
			}
			j++;
		}
		i++;
	}
	return (1);
}

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
	if (y < 0 || x < 0 || !map[y] || (map[y] && !map[y][x]) || map[y][x] == ' ')
		return (1);
	else if (map[y][x] == '1')
		return (0);
	map[y][x] = '1';
	return (ft_flood_fill(map, y - 1, x)
		|| ft_flood_fill(map, y + 1, x)
		|| ft_flood_fill(map, y, x - 1)
		|| ft_flood_fill(map, y, x + 1));
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

	i = first_line_detector(cub);
	if (!check_islands(cub))
		return (printf("Error: Map invalid\n"), free_tab(cub), 0);
	while (cub[i])
	{
		j = 0;
		while (cub[i][j])
		{
			if (cub[i][j] == 'N' || cub[i][j] == 'S'
				|| cub[i][j] == 'W' || cub[i][j] == 'E')
			{
				if (start_parse_map(cub, i, j) != 0)
					return (printf("Error: Map invalid\n"), free_tab(cub), 0);
				else
					return (1);
			}
			j++;
		}
		i++;
	}
	return (printf("Error: Map invalid\n"), free_tab(cub), 0);
}
