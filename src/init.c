/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdakhlao <sdakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 21:09:11 by sdakhlao          #+#    #+#             */
/*   Updated: 2025/09/17 19:59:39 by sdakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	init_image(t_mlx *data, t_details *details)
{
	data->image.north_path = ft_strtrim(details->north, " ");
	if (!data->image.north_path)
		return (0);
	data->image.south_path = ft_strtrim(details->south, " ");
	if (!data->image.south_path)
		return (0);
	data->image.east_path = ft_strtrim(details->east, " ");
	if (!data->image.east_path)
		return (0);
	data->image.west_path = ft_strtrim(details->west, " ");
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
	data->map.texture_w = 64;
	data->map.texture_h = 64;
	data->map.screen_w = WIN_W;
	data->map.screen_h = WIN_H;
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
