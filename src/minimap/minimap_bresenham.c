/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bresenham.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcudos <marcudos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 00:34:45 by marcudos          #+#    #+#             */
/*   Updated: 2025/07/26 01:42:27 by marcudos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

t_bres	set_vars_bres(t_point p0, t_point p1)
{
	t_bres	vars;

	vars.dx = abs(p1.x - p0.x);
	vars.dy = abs(p1.y - p0.y);
	if (p0.x < p1.x)
		vars.sx = 1;
	else
		vars.sx = -1;
	if (p0.y < p1.y)
		vars.sy = 1;
	else
		vars.sy = -1;
	vars.err = vars.dx - vars.dy;
	return (vars);
}

void	draw_bresenham_line(t_game *game, t_point p0, t_point p1, int color)
{
	t_bres	vars;
	int		b_color;

	vars = set_vars_bres(p0, p1);
	(void) color;
	while (1)
	{
		b_color = get_pixel(game->img, p0.x, p0.y);
		put_pixel(game->img, p0.x, p0.y, blend_colors(b_color, COLOR_FOV, 0.2));
		if (p0.x == p1.x && p0.y == p1.y)
			break ;
		vars.e2 = 2 * vars.err;
		if (vars.e2 > -vars.dy)
		{
			vars.err -= vars.dy;
			p0.x += vars.sx;
		}
		if (vars.e2 < vars.dx)
		{
			vars.err += vars.dx;
			p0.y += vars.sy;
		}
	}
}

void	draw_fov(t_game *game, t_point end, int color, t_mini *mini)
{
	t_point	p0;

	end.x += mini->x_offset;
	end.y += mini->y_offset;
	p0.x = (int)(game->cfg->player.x * mini->tile) + mini->x_offset;
	p0.y = (int)(game->cfg->player.y * mini->tile) + mini->y_offset;
	draw_bresenham_line(game, p0, end, color);
}
