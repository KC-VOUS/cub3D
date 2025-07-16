/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsingh <fsingh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 19:18:17 by sdakhlao          #+#    #+#             */
/*   Updated: 2025/07/16 17:03:53 by fsingh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	check_order(char **cub)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cub[i])
		i++;
	i -= 1;
	while (cub[i][j] == ' ')
		j++;
	if (cub[i][j] != '1')
	{
		printf("la map doit etre en dernier\n");
		return (free_tab(cub), 0);
	}
	return (1);
}

int	check_color(char **cub)
{
	int	i;
	int	j;
	int	k = 0;
	int	l = 0;
	char	*str = NULL;

	i = 0;
	j = 1;
	while (cub[i])
	{
		if (!strncmp(cub[i], "F", 1) || !strncmp(cub[i], "C", 1))
		{
			if ((cub[i][1] < '0' || cub[i][1] > '9') && cub[i][1] != ' ')
				return (free_tab(cub), 0);
			while (cub[i][j] == ' ')
				j++;
			if (cub[i][j] < '0' || cub[i][j] > '9')
				return (free_tab(cub), 0);
			k = j;
			while (cub[i][k] > '0' || cub[i][k] < '9')
				k++;
			if (k - j > 3)
				return (free_tab(cub), 0);
			str = malloc(sizeof(char) * (k - j) + 1);
			while (j < k)
			{
				str[l] = cub[i][j];
				j++;
				l++;
			}
			str[l] = '\0';
			if (atoi(str) < 0 || atoi(str) > 255)
				return (free_tab(cub), 0);
			while (cub[i][j] == ' ')
				j++;
			if (cub[i][j] != ',')
				return (free_tab(cub), 0);
		}
		i++;
	}
	return (1);
}

void	check_data(char **cub)
{
	if (!check_order(cub))
		exit(EXIT_FAILURE);
	if (!check_texture(cub))
		exit(EXIT_FAILURE);
	// if (!check_color(cub))
	// 	exit(EXIT_FAILURE);
	if (!check_map(cub))
	 	exit(EXIT_FAILURE);
	if (!check_map_content(cub))
		exit(EXIT_FAILURE);
}
