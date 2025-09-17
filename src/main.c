/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdakhlao <sdakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 20:13:51 by sdakhlao          #+#    #+#             */
/*   Updated: 2025/09/13 19:53:45 by sdakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

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

int	load_texture(void *mlx, char *path, t_tex *tex)
{
	tex->img = mlx_xpm_file_to_image(mlx, path, &tex->w, &tex->h);
	if (!tex->img)
		return (0);
	tex->addr = mlx_get_data_addr(tex->img, &tex->bpp,
			&tex->line_len, &tex->endian);
	return (1);
}

int	check_all_textures(void *mlx, t_mlx *data)
{
	if (!load_texture(mlx, data->image.north_path, &data->image.north))
		return (0);
	if (!load_texture(mlx, data->image.south_path, &data->image.south))
	{
		mlx_destroy_image(data->mlx, data->image.north.img);
		return (0);
	}
	if (!load_texture(mlx, data->image.east_path, &data->image.east))
	{
		mlx_destroy_image(data->mlx, data->image.north.img);
		mlx_destroy_image(data->mlx, data->image.south.img);
		return (0);
	}
	if (!load_texture(mlx, data->image.west_path, &data->image.west))
	{
		mlx_destroy_image(data->mlx, data->image.north.img);
		mlx_destroy_image(data->mlx, data->image.south.img);
		mlx_destroy_image(data->mlx, data->image.east.img);
		return (0);
	}
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
