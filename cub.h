/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdakhlao <sdakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 20:13:43 by sdakhlao          #+#    #+#             */
/*   Updated: 2025/07/23 23:16:30 by sdakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stddef.h>
# include "mlx/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <X11/Xlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

# define WIN_W 640
# define WIN_H 480

typedef struct s_map
{
	int	width;
	int	height;
	int	screen_w;
	int	screen_h;
	int	texture_w;
	int	texture_h;
	int	**map;
}	t_map;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	time;
	int		up;
	int		down;
	int		left;
	int		right;
	int		r_left;
	int		r_right;
}	t_player;

typedef struct s_mlx
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bpp;
	int			size_line;
	int			endian;
	int			x;
	int			y;
	t_map		map;
	t_player	player;
}	t_mlx;

void	free_tab(char **tab);
void	print_tab(char **tab);
void	cp_file(char	*file);
void	check_data(char **cub);
char	*get_next_line(int fd);
int		check_texture(char **cub);
char	*ft_strchr(char *s, int c);
char	*ft_get_line(char *left_str);
int		check_access(char *txtr_path);
char	*ft_new_left_str(char *left_str);
char	*ft_strjoin(char *left_str, char *buff);
char	*ft_read_to_left_str(int fd, char *left_str);

size_t	ft_strlen(char *s);

#endif
