/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caide-so <caide-so@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 19:37:37 by caide-so          #+#    #+#             */
/*   Updated: 2025/07/08 19:45:33 by caide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../lib/libft/include/libft.h"
# include "../lib/minilibx-linux/mlx.h"

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

typedef struct s_color {
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_texture {
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
}	t_texture;

typedef struct s_map {
	char	**grid;
	int		width;
	int		height;
}	t_map;

typedef struct s_player {
	int		x;
	int		y;
	char	dir;
}	t_player;

typedef struct s_config {
	t_texture	texture;
	t_color		floor;
	t_color		ceiling;
	t_map		map;
	t_player	player;
}	t_config;

#endif
