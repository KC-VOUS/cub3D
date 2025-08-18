/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_content.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdakhlao <sdakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 17:01:41 by fsingh            #+#    #+#             */
/*   Updated: 2025/08/18 21:13:19 by sdakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	checking_content(char *cub_line, int *player_count)
{
	int	i;

	i = 0;
	while (cub_line[i])
	{
		if (cub_line[i] == 'N' || cub_line[i] == 'S'
			|| cub_line[i] == 'O' || cub_line[i] == 'E')
			(*player_count)++;
		i++;
	}
	return (1);
}

int	check_invalid_content(char *cub_line)
{
	int	i;

	i = 0;
	while (cub_line[i])
	{
		if (cub_line[i] != 'N' && cub_line[i] != 'S'
			&& cub_line[i] != 'O' && cub_line[i] != 'E' && cub_line[i] != '1'
			&& cub_line[i] != '0' && cub_line[i] != ' ' && cub_line[i] != '\n')
		{
			printf("Invalid character in map\n");
			return (0);
		}
		i++;
	}
	return (1);
}

int	check_map_content(char **cub)
{
	int	i;
	int	player_count;

	player_count = 0;
	i = first_line_detector(cub);
	while (cub[i])
	{
		if (!check_invalid_content(cub[i]))
			return (0);
		checking_content(cub[i], &player_count);
		i++;
	}
	if (player_count != 1)
	{
		printf("there must be exactly one player; found %d\n", player_count);
		return (0);
	}
	return (1);
}
