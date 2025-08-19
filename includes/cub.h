/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsingh <fsingh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 20:13:43 by sdakhlao          #+#    #+#             */
/*   Updated: 2025/08/19 16:41:39 by fsingh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include "mlx/mlx.h"
# include "mlx/mlx_int.h"
# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <sys/time.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <X11/Xlib.h>
# include <math.h>
# include "../libft/libft.h"

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
	char				**map;
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
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bpp;
	int			size_line;
	int			endian;
	int			x;
	int			y;
	t_image		image;
	t_map		map;
	t_player	player;
}	t_mlx;

typedef struct s_map_details
{
	char			**map;
	int				width;
	int				height;
	int				screen_w;
	int				screen_h;
	int				texture_w;
	int				texture_h;
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
	double			plane_x;
	double			plane_y;
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
void	fill_map_details(t_details *details, char **tab);
void	fill_details(t_details *details, char **tab);
void	fill_player(t_details *details, char **tab);
void	init_struct(t_details *details);
void	free_details(t_details *details);
size_t	ft_strlens(char *s);
void	free_it(t_mlx *data);
int		first_line_detector(char **tab);
int			quit(t_mlx *data);
size_t		ft_strlenn(char *s);
void		free_tab(char **tab);
int			check_map(char **cub);
void		print_tab(char **tab);
char		**dup_map(char **cub);
void		check_data(char **cub);
char		*get_next_line(int fd);
int			check_color(char **cub);
int			raycasting(t_mlx *data);
int			rgb(int r, int g, int b);
void		init_player(t_mlx *data);
int			check_texture(char **cub);
char		*ft_strchrr(char *s, int c);
char		*ft_get_line(char *left_str);
void		init_mlx(t_details *details);
int			check_map_content(char **cub);
int			check_access(char *txtr_path);
void		reset_player_move(t_mlx *data);
void		init_struct(t_details *details);
char		*ft_new_left_str(char *left_str);
void		free_details(t_details *details);
char		*ft_strjoinn(char *left_str, char *buff);
int			init_map(t_mlx *data, t_details *details);
int			check_all_textures(void *mlx, t_mlx *data);
int			init_data(t_mlx *data, t_details *details);
void		fill_details(t_details *details, char **tab);
char		*ft_read_to_left_str(int fd, char *left_str);
void		put_pxl(t_mlx *data, int x, int y, int color);
void		check_validity(char	*file, t_details *details);
void		free_image_paths(t_image *image);

#endif
