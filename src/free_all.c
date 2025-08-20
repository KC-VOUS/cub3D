/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsingh <fsingh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 20:47:16 by sdakhlao          #+#    #+#             */
/*   Updated: 2025/08/20 17:55:11 by fsingh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	free_map(char **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	free_image_paths(t_image *image)
{
	if (image->north_path)
		free(image->north_path);
	if (image->south_path)
		free(image->south_path);
	if (image->east_path)
		free(image->east_path);
	if (image->west_path)
		free(image->west_path);
}

void	free_textures(t_mlx *data)
{
	if (data->image.north.img)
		mlx_destroy_image(data->mlx, data->image.north.img);
	if (data->image.south.img)
		mlx_destroy_image(data->mlx, data->image.south.img);
	if (data->image.east.img)
		mlx_destroy_image(data->mlx, data->image.east.img);
	if (data->image.west.img)
		mlx_destroy_image(data->mlx, data->image.west.img);
}

void	free_it(t_mlx *data)
{
	free_image_paths(&data->image);
	free_map(data->map.map);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	exit(EXIT_FAILURE);
}
