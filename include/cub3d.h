/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caide-so <caide-so@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 19:37:37 by caide-so          #+#    #+#             */
/*   Updated: 2025/07/17 22:34:58 by caide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../lib/libft/include/libft.h"
# include "../lib/minilibx-linux/mlx.h"
# include "colors.h"
# include "keys.h"
# include "structs.h"
# include "macros.h"

# include <math.h>

// printf, perror
# include <stdio.h>

// open
# include <fcntl.h>

// close, read, write
# include <unistd.h>

// strerror
# include <string.h>

// malloc, free, exit
# include <stdlib.h>

// gettimeofday
# include <sys/time.h>

// parse
t_cfg	*init_cub(void);
int		parse_cub(char *filename, t_cfg *cfg);

// is_line_functions
int		is_map_line(char *line);
int		is_color_line(char *line);
int		is_texture_line(char *line);
int		is_empty_line(char *line);

// error 
int		error_msg(char *msg);

// check_map
int		check_cub_complete(t_cfg *cfg);

// texture_parser
int		parse_texture_line(t_cfg *cfg, char *line);

// color_parser
int		parse_color_line(t_cfg *cfg, char *line);

// map_collector
int		add_map_line(t_list **map_lines, char *line);
void	convert_list_to_matrix(t_list **map_lines, t_cfg *cfg);

// array
void	free_array(void **arr);

// parse_utils
char	*skip_spaces(char *str);
int		check_line_map(char *line);
int		check_final_file(int fd, char *line, t_list **map_l, t_cfg *cfg);

// parse
void	print_config(t_cfg *cfg);

// free
void	free_game(t_game *game);
void	free_config(t_cfg *cfg);
void	free_map_copy(char **map, int height);
void	free_gnl(int fd);

// init_config
t_cfg	*init_config(void);

// map validation
int		validate_map(t_map *map, t_player *player);
char	**copy_map(t_map *map);

// get_player
void	get_player_position(t_cfg *cfg);

// game
t_game	*init_game(void);

// render
int		render_frame(t_game *game);

// raycast
void	raycast_and_draw(t_game *game);
void	init_ray(t_player *player, t_ray *ray, int x);
void	perform_dda(t_ray *ray, t_game *game);
void	draw_column(t_ray *ray, t_game *game, int x);

#endif
