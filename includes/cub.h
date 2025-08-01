/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsingh <fsingh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 20:13:43 by sdakhlao          #+#    #+#             */
/*   Updated: 2025/07/28 16:55:45 by fsingh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stddef.h>
# include "../libft/libft.h"


# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

typedef struct s_map
{
	char	**map;
	int		width;
	int		height;
} t_map;

typedef struct s_details
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	t_map	map;
	double	player_pos_x;
	double	player_pos_y;
	double	dir_y;
	double	dir_x;
	int		floor_r;
	int		floor_g;
	int		floor_b;
	int		ceiling_r;
	int		ceiling_g;
	int		ceiling_b;
}	t_details;

void	free_tab(char **tab);
void	print_tab(char **tab);
void	cp_file(char	*file, t_details *details);
void	check_data(char **cub);
char	*get_next_line(int fd);
int		check_texture(char **cub);
char	*ft_strchrs(char *s, int c);
char	*ft_get_line(char *left_str);
int		check_access(char *txtr_path);
char	*ft_new_left_str(char *left_str);
char	*ft_strjoins(char *left_str, char *buff);
char	*ft_read_to_left_str(int fd, char *left_str);
int		check_map(char **cub);
int		check_map_content(char **cub);
char	**dup_map(char **cub);
void	fill_details(t_details *details, char **tab);
void	init_struct(t_details *details);
size_t	ft_strlens(char *s);

#endif
