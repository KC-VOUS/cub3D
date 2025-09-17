/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_access.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdakhlao <sdakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 19:18:43 by sdakhlao          #+#    #+#             */
/*   Updated: 2025/09/17 20:25:01 by sdakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

char	*dup_txtr_path(char *txtr_path)
{
	int		i;
	char	*str;

	i = 0;
	while (txtr_path[i] && txtr_path[i] != '\n')
		i++;
	str = malloc(sizeof(char) * i + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (txtr_path[i] && txtr_path[i] != '\n')
	{
		str[i] = txtr_path[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*helpme(char *str, int i)
{
	char	*s;
	int		j;
	int		k;

	k = i;
	j = 0;
	while (str[i] && str[i] != ' ')
	{
		i++;
		j++;
	}
	s = malloc(j * sizeof(char) + 1);
	j = 0;
	while (str[k] && str[k] != ' ')
	{
		s[j] = str[k];
		j++;
		k++;
	}
	s[j] = '\0';
	free (str);
	return (s);
}

int	check_text_acc(char *str)
{
	int	fd;
	int	i;

	i = 2;
	while (str[i] == ' ')
		i++;
	str = helpme(str, i);
	fd = open(str, O_RDONLY);
	if (fd < 0)
	{
		perror("Erreur lors de l'ouverture de la texture");
		free(str);
		return (0);
	}
	close(fd);
	free(str);
	return (1);
}

int	check_text_acc_bis(char *str)
{
	int	fd;

	fd = open(str + 2, O_RDONLY);
	if (fd < 0)
	{
		perror("Erreur lors de l'ouverture de la texture");
		free(str);
		return (0);
	}
	close(fd);
	free(str);
	return (1);
}

int	check_access(char *txtr_path)
{
	int		i;
	char	*str;

	i = 0;
	str = dup_txtr_path(txtr_path);
	if (!str)
		return (0);
	else if (str[2] == ' ')
	{
		if (!check_text_acc(str))
			return (0);
	}
	else
	{
		if (!check_text_acc_bis(str))
			return (0);
	}
	return (1);
}
