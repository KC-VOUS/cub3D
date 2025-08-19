/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsingh <fsingh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 21:26:54 by sdakhlao          #+#    #+#             */
/*   Updated: 2025/08/19 16:20:27 by fsingh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	fill_dir_w(t_details *details)
{
	details->dir_x = 0.0;
	details->dir_y = -1.0;
	details->plane_x = -0.66;
	details->plane_y = 0.0;
}

void	fill_dir(t_details *details, char dir)
{
	if (dir == 'N')
	{
		details->dir_x = -1.0;
		details->dir_y = 0.0;
		details->plane_x = 0.0;
		details->plane_y = 0.66;
	}
	else if (dir == 'S')
	{
		details->dir_x = 1.0;
		details->dir_y = 0.0;
		details->plane_x = 0.0;
		details->plane_y = -0.66;
	}
	else if (dir == 'E')
	{
		details->dir_x = 0.0;
		details->dir_y = 1.0;
		details->plane_x = 0.66;
		details->plane_y = 0.0;
	}
	else if (dir == 'W')
		fill_dir_w(details);
}

void	fill_player(t_details *details, char **tab)
{
	int	i;
	int	j;

	i = 0;
	while (tab[i])
	{
		j = 0;
		while (tab[i][j])
		{
			if (tab[i][j] == 'N' || tab[i][j] == 'E'
				|| tab[i][j] == 'S' || tab[i][j] == 'W')
			{
				details->player_pos_x = i + 0.5;
				details->player_pos_y = j + 0.5;
				fill_dir(details, tab[i][j]);
				return ;
			}
			j++;
		}
		i++;
	}
}
