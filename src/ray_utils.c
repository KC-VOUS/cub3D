/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdakhlao <sdakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 19:49:37 by sdakhlao          #+#    #+#             */
/*   Updated: 2025/09/12 19:35:57 by sdakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	draw_tex(t_ray *r, t_mlx *data, int x)
{
	t_tex	*texture;

	if (r->side == 0)
	{
		if (r->raydirx > 0)
			texture = &data->image.south;
		else
			texture = &data->image.north;
	}
	else
	{
		if (r->raydiry > 0)
			texture = &data->image.east;
		else
			texture = &data->image.west;
	}
	if (r->side == 0)
		r->wallx = data->player.pos_y + r->perpwalldist * r->raydiry;
	else
		r->wallx = data->player.pos_x + r->perpwalldist * r->raydirx;
	r->wallx -= floor(r->wallx);
	r->texx = (int)(r->wallx * (double)texture->w);
	if ((r->side == 0 && r->raydirx > 0) || (r->side == 1 && r->raydiry < 0))
		r->texx = texture->w - r->texx - 1;
	texture_line(data, x, texture, r);
}

void	jsp(t_ray *ray, t_mlx *data, int x, int w)
{
	ray->hit = 0;
	ray->h = data->map.screen_h;
	ray->camerax = 2 * x / (double)w - 1;
	ray->raydirx = data->player.dir_x + data->player.plane_x * ray->camerax;
	ray->raydiry = data->player.dir_y + data->player.plane_y * ray->camerax;
	ray->mapx = (int)data->player.pos_x;
	ray->mapy = (int)data->player.pos_y;
}

void	jspp(t_mlx *data, t_ray *r)
{
	if (r->raydiry == 0)
		r->deltadisty = 1e30;
	else
		r->deltadisty = fabs(1.0 / r->raydiry);
	if (r->raydirx < 0)
	{
		r->stepx = -1;
		r->sidedistx = (data->player.pos_x - r->mapx) * r->deltadistx;
	}
	else
	{
		r->stepx = 1;
		r->sidedistx = (r->mapx + 1.0 - data->player.pos_x) * r->deltadistx;
	}
	if (r->raydiry < 0)
	{
		r->stepy = -1;
		r->sidedisty = (data->player.pos_y - r->mapy) * r->deltadisty;
	}
	else
	{
		r->stepy = 1;
		r->sidedisty = (r->mapy + 1.0 - data->player.pos_y) * r->deltadisty;
	}
}

void	jsppp(t_mlx *data, t_ray *ray)
{
	while (ray->hit == 0)
	{
		if (ray->sidedistx < ray->sidedisty)
		{
			ray->sidedistx += ray->deltadistx;
			ray->mapx += ray->stepx;
			ray->side = 0;
		}
		else
		{
			ray->sidedisty += ray->deltadisty;
			ray->mapy += ray->stepy;
			ray->side = 1;
		}
		if (data->map.map[ray->mapx][ray->mapy] == '1')
			ray->hit = 1;
	}
}

void	get_rays(t_mlx *data, int x, int w)
{
	t_ray	ray;

	jsp(&ray, data, x, w);
	if (ray.raydirx == 0)
		ray.deltadistx = 1e30;
	else
		ray.deltadistx = fabs(1.0 / ray.raydirx);
	jspp(data, &ray);
	jsppp(data, &ray);
	if (ray.side == 0)
		ray.perpwalldist = (ray.sidedistx - ray.deltadistx);
	else
		ray.perpwalldist = (ray.sidedisty - ray.deltadisty);
	ray.lineheight = (int)(ray.h / ray.perpwalldist);
	ray.drawstart = -ray.lineheight / 2 + ray.h / 2;
	if (ray.drawstart < 0)
		ray.drawstart = 0;
	ray.drawend = ray.lineheight / 2 + ray.h / 2;
	if (ray.drawend >= ray.h)
		ray.drawend = ray.h - 1;
	draw_tex(&ray, data, x);
}
