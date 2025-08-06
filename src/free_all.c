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
	if (data->image.north)
		mlx_destroy_image(data->mlx, data->image.north);
	if (data->image.south)
		mlx_destroy_image(data->mlx, data->image.south);
	if (data->image.east)
		mlx_destroy_image(data->mlx, data->image.east);
	if (data->image.west)
		mlx_destroy_image(data->mlx, data->image.west);
}

void	free_all(t_mlx *data)
{
	// free_textures(data);
	free_image_paths(&data->image);
	// free_map(data->map.map);//
	// if (data->img)
	// 	mlx_destroy_image(data->mlx, data->img);
	// if (data->win)
	// 	mlx_destroy_window(data->mlx, data->win);
	// if (data->mlx)
	// {
	// 	mlx_destroy_display(data->mlx);
	// 	free(data->mlx);
	// }
	// exit(EXIT_FAILURE);
}
