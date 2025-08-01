/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caide-so <caide-so@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 02:01:19 by caide-so          #+#    #+#             */
/*   Updated: 2025/08/01 02:56:17 by caide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	setup_sprite(t_sprite *sprite, double x, double y, t_game *game);
int		get_sprite_id(double x, double y);
int		load_sprite_frames_id(t_game *game, t_sprite *sprite, int id);
void	get_sprite_paths(char **paths, int id);

int	init_sprites(t_game *game)
{
	int	y;
	int	x;
	int	i;

	y = 0;
	i = 0;
	while (y < game->cfg->map.height && i < MAX_SPRITES)
	{
		x = 0;
		while (x < game->cfg->map.width && i < MAX_SPRITES)
		{
			if (game->cfg->map.grid[y][x] == 'C')
				setup_sprite(&game->sprites[i++], x + 0.5, y + 0.5, game);
			x++;
		}
		y++;
	}
	game->sprite_count = i;
	return (0);
}

void	setup_sprite(t_sprite *sprite, double x, double y, t_game *game)
{
	sprite->x = x;
	sprite->y = y;
	sprite->current_frame = 0;
	sprite->frame_timer = 0.0;
	sprite->frame_delay = 0.5;
	load_sprite_frames_id(game, sprite, get_sprite_id(x, y));
}

int	get_sprite_id(double x, double y)
{
	int	id;

	id = ((int)(x + y)) % MAX_SPRITES;
	return (id);
}

int	load_sprite_frames_id(t_game *game, t_sprite *sprite, int id)
{
	char	*paths[SPRITE_FRAMES];
	int		i;

	get_sprite_paths(paths, id);
	i = 0;
	while (i < SPRITE_FRAMES)
	{
		sprite->frames[i].img = mlx_xpm_file_to_image(game->mlx, paths[i],
				&sprite->frames[i].width, &sprite->frames[i].height);
		if (!sprite->frames[i].img)
			return (1);
		sprite->frames[i].addr = mlx_get_data_addr(sprite->frames[i].img,
				&sprite->frames[i].bits_per_pixel, &sprite->frames[i].size_len,
				&sprite->frames[i].endian);
		i++;
	}
	return (0);
}

void	get_sprite_paths(char **paths, int id)
{
	if (id == 0)
		fill_zombie1_paths(paths);
	else if (id == 1)
		fill_zombie2_paths(paths);
	else if (id == 2)
		fill_zombie3_paths(paths);
	else if (id == 3)
		fill_zombie4_paths(paths);
}
