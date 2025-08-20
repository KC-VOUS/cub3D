/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsingh <fsingh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 20:13:51 by sdakhlao          #+#    #+#             */
/*   Updated: 2025/08/20 17:50:09 by fsingh           ###   ########.fr       */
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

int load_texture(void *mlx, char *path, t_tex *tex)
{
	tex->img = mlx_xpm_file_to_image(mlx, path, &tex->w, &tex->h);
	if (!tex->img)
		return (0);
	tex->addr = mlx_get_data_addr(tex->img, &tex->bpp, &tex->line_len, &tex->endian);
	return (1);
}

int check_all_textures(void *mlx, t_mlx *data)
{
	if (!load_texture(mlx, data->image.north_path, &data->image.north))
		return (0);
	if (!load_texture(mlx, data->image.south_path, &data->image.south))
		return (0);
    if (!load_texture(mlx, data->image.east_path, &data->image.east))
		return (0);
	if (!load_texture(mlx, data->image.west_path, &data->image.west))
		return (0);
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
