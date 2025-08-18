/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdakhlao <sdakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 23:41:49 by sdakhlao          #+#    #+#             */
/*   Updated: 2025/08/18 22:10:32 by sdakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	quit(t_mlx *data)
{
	mlx_destroy_image(data->mlx, data->img);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	free_tab(data->map.map);
	free_image_paths(&data->image);
	exit(EXIT_FAILURE);
}

int	rgb(int r, int g, int b)
{
	return (0 << 24 | r << 16 | g << 8 | b);
}

void	put_pxl(t_mlx *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x > WIN_W || y < 0 || y > WIN_H)
	{
		printf("Error\nPixel off limit\n");
		quit(data);
	}
	dst = data->addr + (y * data->size_line + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

int	key_hook(int key_code, t_mlx *data)
{
	if (key_code == XK_Escape)
		quit(data);
	else if (key_code == XK_w)
		data->player.up = 1;
	else if (key_code == XK_a)
		data->player.left = 1;
	else if (key_code == XK_s)
		data->player.down = 1;
	else if (key_code == XK_d)
		data->player.right = 1;
	else if (key_code == XK_Left)
		data->player.r_left = 1;
	else if (key_code == XK_Right)
		data->player.r_right = 1;
	return (0);
}

void	init_mlx(t_details *details)
{
	t_mlx	data;

	if (!init_data(&data, details))
	{
		free_details(details);
		return ;
	}
	free_details(details);
	data.mlx = mlx_init();
	if (!check_all_textures(data.mlx, &data))
	{
		write(2, "Error: Invalid texture file(s)\n", 31);
		free_all(&data);
	}
	data.win = mlx_new_window(data.mlx, 640, 480, "cub3D");
	data.img = mlx_new_image(data.mlx, 640, 480);
	data.addr = mlx_get_data_addr(data.img, &data.bpp,
			&data.size_line, &data.endian);
	mlx_hook(data.win, KeyPress, KeyPressMask, &key_hook, &data);
	mlx_hook(data.win, 17, 0, &quit, &data);
	mlx_loop_hook(data.mlx, raycasting, &data);
	mlx_loop(data.mlx);
}
