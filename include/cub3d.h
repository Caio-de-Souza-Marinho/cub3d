/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caide-so <caide-so@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 19:37:37 by caide-so          #+#    #+#             */
/*   Updated: 2025/07/16 20:37:57 by caide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../lib/libft/include/libft.h"
# include "../lib/minilibx-linux/mlx.h"
# include "colors.h"

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

// Macros
# ifndef WIN_HEIGHT
#  define WIN_HEIGHT 720
# endif

# ifndef WIN_WIDTH
#  define WIN_WIDTH 1280
# endif

// Stucts
typedef struct s_color
{
	int		r;
	int		g;
	int		b;
}	t_color;

typedef struct s_texture
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
}	t_texture;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
}	t_map;

typedef struct s_player
{
	float	x;
	float	y;
	char	dir;
}	t_player;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		size_len;
	int		endian;
}	t_img;

typedef struct s_cfg
{
	t_color		ceiling;
	t_color		floor;
	t_texture	texture;
	t_map		map;
	t_player	player;
}	t_cfg;

typedef struct s_game
{
	t_cfg	*cfg;
	void	*mlx;
	void	*win;
	t_img	*img;
}	t_game;

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

// free_config
void	free_config(t_cfg *cfg);
void	free_gnl(int fd);

// init_config
t_cfg	*init_config(void);

// map validation
int		validate_map(t_map *map, t_player *player);
char	**copy_map(t_map *map);

// map validation clean
void	free_map_copy(char **map, int height);

// get_player
void	get_player_position(t_cfg *cfg);

#endif
