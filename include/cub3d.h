/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caide-so <caide-so@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 19:37:37 by caide-so          #+#    #+#             */
/*   Updated: 2025/07/11 19:37:05 by marcudos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include "../lib/libft/include/libft.h"

// Stucts
typedef struct s_color
{
	int	r;
	int	g;
	int	b;
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
	int	width;
	int	height;
}	t_map;

typedef struct s_player
{
	int	x;
	int	y;
	char	dir;
}	t_player;

typedef struct s_config
{
	t_texture	texture;
	t_color	floor;
	t_color	ceiling;
	t_map	map;
	t_player	player;
}	t_config;


t_config	*init_cub();
int		parse_cub(char *filename, t_config *cfg);

// is_line_functions
int		is_map_line(char *line);
int		is_color_line(char *line);
int		is_texture_line(char *line);
int		is_empty_line(char *line);

// error 
int	error_msg(char *msg);

// check_map
int	check_line_map(char *line);
int	check_final_file(int fd, char *line, t_list **map_lines, t_config *cfg);

// texture_parser
int	parse_texture_line(t_config *cfg, char *line);

// color_parser
int	parse_color_line(t_config *cfg, char *line);

// map_collector
int	add_map_line(t_list **map_lines, char *line);
void	convert_list_to_matrix(t_list **map_lines, t_config *cfg);

// array
void	free_array(void **arr);

// parse_utils
char	*skip_spaces(char *str);

// parse
void	print_config(t_config *cfg);

// free_config
void	free_config(t_config *cfg);

// init_config
t_config	*init_config(void);
#endif
