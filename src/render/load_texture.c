/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caide-so <caide-so@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 20:13:00 by caide-so          #+#    #+#             */
/*   Updated: 2025/07/18 20:22:59 by caide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	load_texture(void *mlx, t_tex *tex);

// Load all textures required by the game.
// 1. Gets texture struct from game config.
// 2. Loads north, sourh, east and west textures using load_texture().
// 3. Sets default door texture path and loads it.
// 4. Returns 0 on success, 1 on failure.
int	load_all_textures(t_game *game)
{
	t_texture	*tex;

	tex = &game->cfg->texture;
	if (load_texture(game->mlx, &tex->no))
		return (1);
	if (load_texture(game->mlx, &tex->so))
		return (1);
	if (load_texture(game->mlx, &tex->we))
		return (1);
	if (load_texture(game->mlx, &tex->ea))
		return (1);
	tex->door.path = "textures/pixel_door.xpm";
	if (tex->door.path && load_texture(game->mlx, &tex->door))
		return (1);
	return (0);
}

// Loads an XPM texture into memory and extracts its data.
// 1. Checks if texture path is valid.
// 2. Loads image from file with mlx_xpm_file_to_image().
// 3. Gets pixel buffer with mlx_get_data_addr().
// 4. Logs error and returns 1 if loading fails at any step.
// 5. Returns 0 on success.
int	load_texture(void *mlx, t_tex *tex)
{
	if (!tex->path)
		return (1);
	tex->img = mlx_xpm_file_to_image(mlx, tex->path, &tex->width,
			&tex->height);
	if (!tex->img)
		return (printf("Failed to load texture: %s\n", tex->path), 1);
	tex->addr = mlx_get_data_addr(tex->img, &tex->bits_per_pixel,
			&tex->size_len, &tex->endian);
	if (!tex->addr)
		return (printf("Failed to get texture data: %s\n", tex->path), 1);
	return (0);
}
