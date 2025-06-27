/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdakhlao <sdakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 20:13:43 by sdakhlao          #+#    #+#             */
/*   Updated: 2025/06/25 19:17:47 by sdakhlao         ###   ########.fr       */
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

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

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
