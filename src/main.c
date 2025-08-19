/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsingh <fsingh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 20:13:51 by sdakhlao          #+#    #+#             */
/*   Updated: 2025/08/19 16:36:26 by fsingh           ###   ########.fr       */
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

void	*check_txt_path(char *path, void *mlx)
{
	int		w;
	int		h;
	void	*img;

	w = 32;
	h = 32;
	if (!has_xpm(path))
		return (NULL);
	img = mlx_xpm_file_to_image(mlx, path, &w, &h);
	if (!img)
		return (NULL);
	return (img);
}

int	check_all_textures(void *mlx, t_mlx *data)
{
	data->image.north = check_txt_path(data->image.north_path, mlx);
	data->image.south = check_txt_path(data->image.south_path, mlx);
	data->image.east = check_txt_path(data->image.east_path, mlx);
	data->image.west = check_txt_path(data->image.west_path, mlx);
	if (!(data->image.north) || !(data->image.south) || !(data->image.east)
		|| !(data->image.west))
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
