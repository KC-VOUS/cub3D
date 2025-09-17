/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdakhlao <sdakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 19:49:27 by sdakhlao          #+#    #+#             */
/*   Updated: 2025/09/12 19:21:05 by sdakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	handle_right_left(t_mlx *data, double movespeed)
{
	if (data->player.right == 1)
	{
		if (data->map.map[(int)(data->player.pos_x + data->player.dir_y
				* (movespeed * 2))][(int)data->player.pos_y] != '1')
			data->player.pos_x += data->player.dir_y * movespeed;
		if (data->map.map[(int)data->player.pos_x][(int)(data->player.pos_y
			- data->player.dir_x * (movespeed * 2))] != '1')
			data->player.pos_y -= data->player.dir_x * movespeed;
	}
	if (data->player.left == 1)
	{
		if (data->map.map[(int)(data->player.pos_x - data->player.dir_y
				* (movespeed * 2))][(int)data->player.pos_y] != '1')
			data->player.pos_x -= data->player.dir_y * movespeed;
		if (data->map.map[(int)data->player.pos_x][(int)(data->player.pos_y
			+ data->player.dir_x * (movespeed * 2))] != '1')
			data->player.pos_y += data->player.dir_x * movespeed;
	}
}

void	handle_up(t_mlx *data, double movespeed)
{
	if (data->map.map[(int)(data->player.pos_x + data->player.dir_x
			* movespeed)][(int)(data->player.pos_y)] != '1')
	data->player.pos_x += data->player.dir_x * movespeed;
	if (data->map.map[(int)(data->player.pos_x)][(int)(data->player.pos_y
		+ data->player.dir_y * movespeed)] != '1')
	data->player.pos_y += data->player.dir_y * movespeed;
}

void	handle_r_right(t_mlx *data, double rotspeed)
{
	double	oldirx;
	double	oldplanex;

	oldirx = data->player.dir_x;
	oldplanex = data->player.plane_x;
	data->player.dir_x = data->player.dir_x * cos(-rotspeed)
		- data->player.dir_y * sin(-rotspeed);
	data->player.dir_y = oldirx * sin(-rotspeed) + data->player.dir_y
		* cos(-rotspeed);
	data->player.plane_x = data->player.plane_x * cos(-rotspeed)
		- data->player.plane_y * sin(-rotspeed);
	data->player.plane_y = oldplanex * sin(-rotspeed)
		+ data->player.plane_y * cos(-rotspeed);
}

void	handle_r_left(t_mlx *data, double rotspeed)
{
	double	oldirx;
	double	oldplanex;

	oldirx = data->player.dir_x;
	oldplanex = data->player.plane_x;
	data->player.dir_x = data->player.dir_x * cos(rotspeed)
		- data->player.dir_y * sin(rotspeed);
	data->player.dir_y = oldirx * sin(rotspeed) + data->player.dir_y
		* cos(rotspeed);
	data->player.plane_x = data->player.plane_x * cos(rotspeed)
		- data->player.plane_y * sin(rotspeed);
	data->player.plane_y = oldplanex * sin(rotspeed) + data->player.plane_y
		* cos(rotspeed);
}

void	handle_movement(t_mlx *data)
{
	double	movespeed;
	double	rotspeed;

	movespeed = 0.016;
	rotspeed = 0.01;
	if (data->player.up == 1)
		handle_up(data, movespeed);
	if (data->player.down == 1)
	{
		if (data->map.map[(int)(data->player.pos_x - data->player.dir_x
				* movespeed)][(int)(data->player.pos_y)] != '1')
			data->player.pos_x -= data->player.dir_x * movespeed;
		if (data->map.map[(int)(data->player.pos_x)][(int)(data->player.pos_y
			- data->player.dir_y * movespeed)] != '1')
			data->player.pos_y -= data->player.dir_y * movespeed;
	}
	if (data->player.r_right == 1)
		handle_r_right(data, rotspeed);
	if (data->player.r_left == 1)
		handle_r_left(data, rotspeed);
	handle_right_left(data, movespeed);
}
