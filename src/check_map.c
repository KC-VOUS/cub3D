/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsingh <fsingh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 18:26:12 by sdakhlao          #+#    #+#             */
/*   Updated: 2025/07/01 18:44:57 by fsingh           ###   ########.fr       */
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
	/*res = ft_flood_fill(map, y, x);*/
	free_tab(map);
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
			printf("on est sur %c et en %d et %d\n", cub[i][j], i, j);
			if (cub[i][j] == '0')
				return (start_parse_map(cub, i, j));
		}
		i++;
	}
	return (0);
}
