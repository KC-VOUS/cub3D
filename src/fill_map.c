/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdakhlao <sdakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 21:27:02 by sdakhlao          #+#    #+#             */
/*   Updated: 2025/08/18 22:11:40 by sdakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	width_detector(char *tab)
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
		j = ft_strlen(tab[i]);
		if (j > max)
			max = j;
		i++;
	}
	details->map.width = max;
	details->map.height = i;
}

int	first_line_detector(char **tab)
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
							break ;
						j++;
					}
					if (tab[i][j] == '1')
						break ;
					i++;
				}
				start_map = i;
			}
			break ;
		}
		i++;
	}
	return (start_map);
}

void	map_line(t_details *details, char **tab, int start_map, int i)
{
	char	*clean;

	clean = NULL;
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
}

void	fill_map_details(t_details *details, char **tab)
{
	int		i;
	int		start_map;
	int		map_lines;

	i = 0;
	map_lines = 0;
	start_map = first_line_detector(tab);
	while (tab[start_map + map_lines])
		map_lines++;
	details->map.map = malloc(sizeof(char *) * (map_lines + 1));
	i = 0;
	while (i < map_lines)
	{
		map_line(details, tab, start_map, i);
		i++;
	}
	details->map.map[i] = NULL;
	map_size(details, details->map.map);
}
