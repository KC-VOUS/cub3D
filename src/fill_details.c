/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_details.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsingh <fsingh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 14:40:08 by fsingh            #+#    #+#             */
/*   Updated: 2025/08/16 13:47:55 by fsingh           ###   ########.fr       */
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
		return;
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
			get_color(tab[i], &details->floor_r, &details->floor_g, &details->floor_b);
		else if (!ft_strncmp(tab[i], "C ", 2))
			get_color(tab[i], &details->ceiling_r, &details->ceiling_g, &details->ceiling_b);
		i++;
	}
}

int		width_detector(char *tab)
{
	int		start;
	int		end;

	end = 0;
	start = 0;
	while (tab[start] == ' ')
		start++;
	end = (ft_strlen(tab) - 1);
	while (end > start && tab[end] == ' ')
		end--;
	return (end - start + 1);
}

void	map_size(t_details *details, char **tab)
{
	int	i;
	int	j;
	int	max;
	
	i = 0;
	max = 0;
	while (tab[i])
	{
		j = width_detector(tab[i]);
		if (j > max)
			max = j;
		i++;
	}
	details->map.width = max;
	details->map.height = i;
}

int		first_line_detector(char **tab)
{
	int	i;
	int	start_map;
	int	j;
	
	i = 0;
	j = 0;
	start_map = 0;
	while (tab[i])
	{
		if (tab[i][0] == ' ' || tab[i][0] == '1')
		{
			if (tab[i][0] == '1')
				start_map = i;
			else
			{
				while (tab[i])
				{
					j = 0;
					while (tab[i][j])
					{
						if (tab[i][j] == '1')
							break;
						j++;
					}
					if (tab[i][j] == '1')
						break;
					i++;
				}
				start_map = i;
			}
			break;
		}
		i++;
	}
	return (start_map);
}

void	fill_map_details(t_details *details, char **tab)
{
	int		i;
	int		start_map;
	int		map_lines;
	char	*clean;

	i = 0;
	map_lines = 0;
	start_map = first_line_detector(tab);
	while (tab[start_map + map_lines])
		map_lines++;
	details->map.map = malloc(sizeof(char *) * (map_lines + 1));
	i = 0;
	while (i < map_lines)
	{
		if (tab[start_map + i])
		{
			clean = ft_strtrim(tab[start_map + i], "\n");
			if (!clean)
				details->map.map[i] = ft_strdup("");
			else
			{
				details->map.map[i] = ft_strdup(clean);
				free(clean);
			}
		}
		else
			details->map.map[i] = ft_strdup("");
		i++;
	}
	details->map.map[i] = NULL;
	map_size(details, details->map.map);
}

void	print_details(t_details *details)
{
	int i = 0;

	printf("NO:%s\n", details->north);
	printf("SO:%s\n", details->south);
	printf("WE:%s\n", details->west);
	printf("EA:%s\n", details->east);
	printf("Floor:R=%d G=%d B=%d\n", details->floor_r, details->floor_g, details->floor_b);
	printf("Ceiling:R=%d G=%d B=%d\n", details->ceiling_r, details->ceiling_g, details->ceiling_b);
	printf("Position:x=%.2f y=%.2f\n", details->player_pos_x, details->player_pos_y);
	printf("Direction:x=%.2f y=%.2f\n", details->dir_x, details->dir_y);
	printf("Map(%d x %d):\n", details->map.height, details->map.width);
	while (details->map.map && details->map.map[i])
	{
		printf("'%s'", details->map.map[i]);
		printf("\n");
		i++;
	}
	printf("données recuperer par le fill_details dans la struct details ^\n");
}

void	free_details(t_details *details)
{
	int	i = 0;

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

void	fill_dir(t_details *details, char dir)
{
	if (dir == 'N')
	{
		details->dir_y = 0;
		details->dir_x = -1;
	}
	else if (dir == 'S')
	{
		details->dir_y = 0;
		details->dir_x = 1;
	}
	else if (dir == 'E')
	{
		details->dir_y = 1;
		details->dir_x = 0;
	}
	else if (dir == 'W')
	{
		details->dir_y = -1;
		details->dir_x = 0;
	}
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

void	fill_details(t_details *details, char **tab)
{
	fill_texture(details, tab);
	fill_color(details, tab);
	fill_map_details(details, tab);
	fill_player(details, details->map.map);
	print_details(details);
	//free_details(details);
}
