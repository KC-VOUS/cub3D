/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdakhlao <sdakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 14:40:08 by fsingh            #+#    #+#             */
/*   Updated: 2025/08/18 21:23:03 by sdakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	fill_texture(t_details *details, char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		if (!ft_strncmp(tab[i], "NO", 2))
			details->north = ft_strtrim(tab[i] + 2, " \n");
		else if (!ft_strncmp(tab[i], "SO", 2))
			details->south = ft_strtrim(tab[i] + 2, " \n");
		else if (!ft_strncmp(tab[i], "WE", 2))
			details->west = ft_strtrim(tab[i] + 2, " \n");
		else if (!ft_strncmp(tab[i], "EA", 2))
			details->east = ft_strtrim(tab[i] + 2, " \n");
		i++;
	}
}

void	get_color(char	*line, int *red, int *green, int *blue)
{
	char	**rgb;

	while (*line == ' ' || *line == 'F' || *line == 'C')
		line++;
	rgb = ft_split(line, ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2])
	{
		if (rgb)
			free_tab(rgb);
		return ;
	}
	*red = ft_atoi(rgb[0]);
	*green = ft_atoi(rgb[1]);
	*blue = ft_atoi(rgb[2]);
	free_tab(rgb);
}

void	fill_color(t_details *details, char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		if (!ft_strncmp(tab[i], "F ", 2))
			get_color(tab[i], &details->floor_r, &details->floor_g,
				&details->floor_b);
		else if (!ft_strncmp(tab[i], "C ", 2))
			get_color(tab[i], &details->ceiling_r, &details->ceiling_g,
				&details->ceiling_b);
		i++;
	}
}

void	free_details(t_details *details)
{
	int	i;

	i = 0;
	if (details->north)
		free(details->north);
	if (details->south)
		free(details->south);
	if (details->west)
		free(details->west);
	if (details->east)
		free(details->east);
	if (details->map.map)
	{
		while (details->map.map[i])
			free(details->map.map[i++]);
		free(details->map.map);
	}
}

void	fill_details(t_details *details, char **tab)
{
	fill_texture(details, tab);
	fill_color(details, tab);
	fill_map_details(details, tab);
	fill_player(details, details->map.map);
	free_tab(tab);
}
