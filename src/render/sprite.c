/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caide-so <caide-so@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 22:36:45 by caide-so          #+#    #+#             */
/*   Updated: 2025/07/22 22:54:04 by caide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	load_sprite_frames(t_game *game, t_sprite *sprite)
{
	char	*paths[SPRITE_FRAMES];
	int		i;
	int		width;
	int		height;

	paths[0] = "textures/east.xpm";
	paths[1] = "textures/north.xpm";
	paths[2] = "textures/sough.xpm";
	paths[3] = "textures/west.xpm";
	i = 0;
	while (i < SPRITE_FRAMES)
	{
		sprite->frames[i] = mlx_xpm_file_to_image(game->mlx, paths[i],
				&width, &height);
		if (!sprite->frames[i])
			return (1);
		i++;
	}
	sprite->current_frame = 0;
	sprite->frame_delay = 0.15;
	sprite->frame_timer = 0.0;
	return (0);
}

void	update_sprite_animation(t_sprite *sprite, double delta)
{
	sprite->frame_timer += delta;
	if (sprite->frame_timer >= sprite->frame_delay)
	{
		sprite->current_frame = (sprite->current_frame + 1) % SPRITE_FRAMES;
		sprite->frame_timer = 0.0;
	}
}

void	draw_sprite(t_game *game)
{
	t_sprite	*sprite;
	void		*img;
	int			screen_x;
	int			screen_y;

	sprite = &game->sprite;
	img = sprite->frames[sprite->current_frame];
	screen_x = WIN_WIDTH / 2;
	screen_y = WIN_HEIGHT / 2;
	mlx_put_image_to_window(game->mlx, game->win, img, screen_x - 32,
		screen_y - 32);
}
