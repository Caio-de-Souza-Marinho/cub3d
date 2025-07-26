/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcudos <marcudos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 13:54:18 by marcudos          #+#    #+#             */
/*   Updated: 2025/07/26 01:05:52 by marcudos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	draw_minimap(t_game *game)
{
	draw_minimap_grid(game);
	draw_minimap_fov(game);
	draw_minimap_player(game);
}

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	dst = img->addr + (y * img->size_len + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	get_pixel(t_img *img, int x, int y)
{
	char	*pixel;
	int		color;

	pixel = img->addr + (y * img->size_len + x * (img->bits_per_pixel / 8));
	color = *(unsigned int *)pixel;
	return (color);
}

int	blend_colors(int base, int overlay, double alpha)
{
	int	r, g, b;

	r = (int)(((overlay >> 16 & 0xFF) * alpha) + ((base >> 16 & 0xFF) * (1 - alpha)));
	g = (int)(((overlay >> 8 & 0xFF) * alpha) + ((base >> 8 & 0xFF) * (1 - alpha)));
	b = (int)(((overlay & 0xFF) * alpha) + ((base & 0xFF) * (1 - alpha)));
	return ((r << 16) | (g << 8) | b);
}
