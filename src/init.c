/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsingh <fsingh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 21:09:11 by sdakhlao          #+#    #+#             */
/*   Updated: 2025/08/20 19:50:24 by fsingh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	init_image(t_mlx *data, t_details *details)
{
	data->image.north_path = strdup(details->north);
	if (!data->image.north_path)
		return (0);
	data->image.south_path = strdup(details->south);
	if (!data->image.south_path)
		return (0);
	data->image.east_path = strdup(details->east);
	if (!data->image.east_path)
		return (0);
	data->image.west_path = strdup(details->west);
	if (!data->image.west_path)
		return (0);
	return (1);
}

int	init_map(t_mlx *data, t_details *details)
{
	data->map.map = dup_map(details->map.map);
	data->map.floor_r = details->floor_r;
	data->map.floor_g = details->floor_g;
	data->map.floor_b = details->floor_b;
	data->map.ceiling_r = details->ceiling_r;
	data->map.ceiling_g = details->ceiling_g;
	data->map.ceiling_b = details->ceiling_b;
	data->map.texture_w = 32;
	data->map.texture_h = 32;
	data->map.screen_w = 640;
	data->map.screen_h = 480;
	data->map.width = details->map.width;
	data->map.height = details->map.height;
	return (1);
}

int	init_data(t_mlx *data, t_details *details)
{
	if (!init_image(data, details))
		return (0);
	if (!init_map(data, details))
		return (0);
	data->player.pos_x = details->player_pos_x;
	data->player.pos_y = details->player_pos_y;
	data->player.dir_x = details->dir_x;
	data->player.dir_y = details->dir_y;
	data->player.plane_x = details->plane_x;
	data->player.plane_y = details->plane_y;
	data->player.time = 0;
	data->player.up = 0;
	data->player.down = 0;
	data->player.left = 0;
	data->player.right = 0;
	data->player.r_left = 0;
	data->player.r_right = 0;
	return (1);
}
