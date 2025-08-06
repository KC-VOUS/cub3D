/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdakhlao <sdakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 20:13:51 by sdakhlao          #+#    #+#             */
/*   Updated: 2025/08/06 15:22:21 by sdakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	reset_player_move(t_mlx *data)
{
	data->player.up = 0;
	data->player.down = 0;
	data->player.left = 0;
	data->player.right = 0;
	data->player.r_right = 0;
	data->player.r_left = 0;
}

int	has_xpm(const char *path)
{
	int	len;

	if (!path)
		return (0);
	len = ft_strlen(path);
	if (len < 4)
		return (0);
	return (ft_strncmp(path + (len - 4), ".xpm", 4) == 0);
}

void	*check_texture_path(char *path, void *mlx)
{
	int		w;
	int		h;
	void	*img;

	w = 64;
	h = 64;
	if (!has_xpm(path))
		return (NULL);
	img = mlx_xpm_file_to_image(mlx, path, &w, &h);
	if (!img)
		return (NULL);
	return (img);
}

int	check_all_textures(void *mlx, t_mlx *data)
{
	if (!(data->image.north = check_texture_path(data->image.north_path, mlx))
		|| !(data->image.south = check_texture_path(data->image.south_path, mlx))
		|| !(data->image.east = check_texture_path(data->image.east_path, mlx))
		|| !(data->image.west = check_texture_path(data->image.west_path, mlx)))
		return (0);
	return (1);
}

int		init_image(t_mlx *data, t_details *details)
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

int		init_map(t_mlx *data, t_details *details)
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
	data->map.screen_w = 640;
	data->map.screen_h = 480;
	data->map.width = details->map.width;
	data->map.height = details->map.height;
	return (1);
}

int		init_data(t_mlx *data, t_details *details)
{
	if (!init_image(data, details))
		return (0);
	if (!init_map(data, details))
		return (0);
	data->player.pos_x = details->player_pos_x;
	data->player.pos_y = details->player_pos_y;
	data->player.dir_x = details->dir_x;
	data->player.dir_y = details->dir_y;
	data->player.plane_x = 0;
	data->player.plane_y = 0.66;
	data->player.time = 0;
	data->player.up = 0;
	data->player.down = 0;
	data->player.left = 0;
	data->player.right = 0;
	data->player.r_left = 0;
	data->player.r_right = 0;
	return (1);
}

int	main(int argc, char **argv)
{
	t_details	details;

	if (argc == 2)
	{
		check_validity(argv[1], &details);
		init_mlx(&details);
	}
	else
	{
		write(2, "Error: Wrong number of arguments\n", 34);
		write(2, "Expected: ./cub3D exemple.cub\n", 31);
		exit(EXIT_SUCCESS);
	}
}
