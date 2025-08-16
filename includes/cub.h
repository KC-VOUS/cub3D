/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsingh <fsingh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 20:13:43 by sdakhlao          #+#    #+#             */
/*   Updated: 2025/08/16 13:20:22 by fsingh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <string.h>
# include <stddef.h>
# include "../libft/libft.h"
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
	int				width;
	int				height;
	int				screen_w;
	int				screen_h;
	int				texture_w;
	int				texture_h;
	int				floor_r;
	int				floor_g;
	int				floor_b;
	int				ceiling_r;
	int				ceiling_g;
	int				ceiling_b;
	char			**map;
}	t_map;

typedef struct s_player
{
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	double			time;
	int				up;
	int				down;
	int				left;
	int				right;
	int				r_left;
	int				r_right;
}	t_player;

typedef struct s_image
{
	char			*north_path;
	char			*south_path;
	char			*east_path;
	char			*west_path;
	void			*north;
	void			*south;
	void			*east;
	void			*west;
} t_image;

typedef struct s_mlx
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*addr;
	int				bpp;
	int				size_line;
	int				endian;
	int				x;
	int				y;
	t_image			image;
	t_map			map;
	t_player		player;
}	t_mlx;

typedef struct s_map_details
{
	char			**map;
	int				width;
	int				height;
} t_map_details;

typedef struct s_details
{
	char			*north;
	char			*south;
	char			*west;
	char			*east;
	t_map_details	map;
	double			player_pos_x;
	double			player_pos_y;
	double			dir_y;
	double			dir_x;
	int				floor_r;
	int				floor_g;
	int				floor_b;
	int				ceiling_r;
	int				ceiling_g;
	int				ceiling_b;
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
void	free_details(t_details *details);
size_t	ft_strlens(char *s);
void	free_all(t_mlx *data);
int		first_line_detector(char **tab);

#endif
