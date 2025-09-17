/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdakhlao <sdakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 18:25:23 by sdakhlao          #+#    #+#             */
/*   Updated: 2025/09/12 17:13:53 by sdakhlao         ###   ########.fr       */
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
	details->map.screen_h = WIN_H;
	details->map.screen_w = WIN_W;
	details->map.texture_h = 64;
	details->map.texture_w = 64;
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

int	key_release(int key_code, t_mlx *data)
{
	if (key_code == XK_w)
		data->player.up = 0;
	if (key_code == XK_a)
		data->player.left = 0;
	if (key_code == XK_s)
		data->player.down = 0;
	if (key_code == XK_d)
		data->player.right = 0;
	if (key_code == XK_Left)
		data->player.r_left = 0;
	if (key_code == XK_Right)
		data->player.r_right = 0;
	return (0);
}
