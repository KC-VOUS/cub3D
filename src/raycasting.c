/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdakhlao <sdakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 19:49:42 by sdakhlao          #+#    #+#             */
/*   Updated: 2025/09/12 19:35:36 by sdakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	draw_floor(t_mlx *data)
{
	int	y;
	int	x;

	y = WIN_H;
	while (y >= WIN_H / 2)
	{
		x = 0;
		while (x <= WIN_W)
		{
			put_pxl(data, x, y, rgb(data->map.floor_r, data->map.floor_g,
					data->map.floor_b));
			x++;
		}
		y--;
	}
}

void	f_c(t_mlx *data)
{
	int	y;
	int	x;

	y = 0;
	while (y <= WIN_H / 2)
	{
		x = 0;
		while (x <= WIN_W)
		{
			put_pxl(data, x, y, rgb(data->map.ceiling_r, data->map.ceiling_g,
					data->map.ceiling_b));
			x++;
		}
		y++;
	}
	draw_floor(data);
}

void	texture_line(t_mlx *data, int screen_x, t_tex *tex, t_ray *ray)
{
	int		y;
	char	*p;

	ray->step = (double)tex->h / (double)ray->lineheight;
	ray->texpos = (ray->drawstart - data->map.screen_h / 2.0
			+ ray->lineheight / 2.0) * ray->step;
	if (ray->drawstart < 0)
		ray->drawstart = 0;
	if (ray->drawend >= data->map.screen_h)
		ray->drawend = data->map.screen_h - 1;
	y = ray->drawstart;
	while (y <= ray->drawend)
	{
		ray->tex_y = (int)ray->texpos;
		if (ray->tex_y < 0)
			ray->tex_y = 0;
		if (ray->tex_y >= tex->h)
			ray->tex_y = tex->h - 1;
		ray->texpos += ray->step;
		p = tex->addr + ray->tex_y * tex->line_len + ray->texx * (tex->bpp / 8);
		ray->color = *(int *)p;
		put_pxl(data, screen_x, y, ray->color);
		y++;
	}
}

int	raycasting(t_mlx *data)
{
	int	w;
	int	x;

	x = 0;
	w = WIN_W;
	f_c(data);
	while (x < w)
	{
		get_rays(data, x, w);
		x++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	handle_movement(data);
	mlx_destroy_image(data->mlx, data->img);
	data->img = mlx_new_image(data->mlx, data->map.screen_w,
			data->map.screen_h);
	if (!data->img)
		return (printf("Error\nImage fail\n"), -1);
	return (0);
}
