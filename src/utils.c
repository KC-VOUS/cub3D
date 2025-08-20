/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsingh <fsingh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 18:25:23 by sdakhlao          #+#    #+#             */
/*   Updated: 2025/08/20 19:51:23 by fsingh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	init_struct(t_details *details)
{
	details->north = NULL;
	details->south = NULL;
	details->west = NULL;
	details->east = NULL;
	details->map.map = NULL;
	details->map.width = 0;
	details->map.height = 0;
	details->map.screen_h = 480;
	details->map.screen_w = 640;
	details->map.texture_h = 32;
	details->map.texture_w = 32;
	details->player_pos_x = 0;
	details->player_pos_y = 0;
	details->dir_x = 0;
	details->dir_y = 0;
	details->floor_r = -1;
	details->floor_g = -1;
	details->floor_b = -1;
	details->ceiling_r = -1;
	details->ceiling_g = -1;
	details->ceiling_b = -1;
}

void	print_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		printf("%s", tab[i]);
		i++;
	}
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
