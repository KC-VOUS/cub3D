/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdakhlao <sdakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 19:18:28 by sdakhlao          #+#    #+#             */
/*   Updated: 2025/08/03 22:54:06 by sdakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	check_no(char *line, int *count)
{
	if (!strncmp(line, "NO", 2))
	{
		if (!check_access(line))
			return (0);
		*(count) += 1;
	}
	return (1);
}

int	check_so(char *line, int *count)
{
	if (!strncmp(line, "SO", 2))
	{
		if (!check_access(line))
			return (0);
		*(count) += 2;
	}
	return (1);
}

int	check_ea(char *line, int *count)
{
	if (!strncmp(line, "EA", 2))
	{
		if (!check_access(line))
			return (0);
		*(count) += 3;
	}
	return (1);
}

int	check_we(char *line, int *count)
{
	if (!strncmp(line, "WE", 2))
	{
		if (!check_access(line))
			return (0);
		*(count) += 4;
	}
	return (1);
}

int	check_texture(char **cub)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cub[i])
	{
		if (!check_no(cub[i], &j))
			return (free_tab(cub), 0);
		else if (!check_so(cub[i], &j))
			return (free_tab(cub), 0);
		else if (!check_ea(cub[i], &j))
			return (free_tab(cub), 0);
		else if (!check_we(cub[i], &j))
			return (free_tab(cub), 0);
		i++;
	}
	if (j != 10)
	{
		printf("Error: problemes avec les textures\n");
		return (free_tab(cub), 0);
	}
	return (1);
}
