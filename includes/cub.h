/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsingh <fsingh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 20:13:43 by sdakhlao          #+#    #+#             */
/*   Updated: 2025/07/16 17:02:37 by fsingh           ###   ########.fr       */
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

void	free_tab(char **tab);
void	print_tab(char **tab);
void	cp_file(char	*file);
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

size_t	ft_strlens(char *s);

#endif
