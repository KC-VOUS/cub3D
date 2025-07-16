/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_content.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsingh <fsingh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 17:01:41 by fsingh            #+#    #+#             */
/*   Updated: 2025/07/16 17:54:54 by fsingh           ###   ########.fr       */
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

int	check_map_content(char **cub)
{
	int	i;
	int	player_count;

	player_count = 0;
	i = 0;
	while (cub[i] && cub[i][0] != ' ' && cub[i][0] != '1')
		i++;
	while (cub[i])
	{
		if (!checking_content(cub[i], &player_count))
			return (0);
		i++;
	}
	if (player_count != 1)
		return (printf("there must be exactly one player; found %d\n", player_count), 0);
	return (1);
}
