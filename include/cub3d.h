/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caide-so <caide-so@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 19:37:37 by caide-so          #+#    #+#             */
/*   Updated: 2025/07/09 18:46:10 by marcudos         ###   ########.fr       */
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

#endif
