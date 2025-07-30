/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcudos <marcudos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 00:39:24 by marcudos          #+#    #+#             */
/*   Updated: 2025/07/25 01:14:08 by marcudos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	handle_door(t_game *game)
{
	char	**grid;
	double	new_xy[2];

	grid = game->cfg->map.grid;
	new_xy[0] = game->cfg->player.y;
	new_xy[1] = game->cfg->player.x;
	if (grid[(int)new_xy[0]][(int)new_xy[1]] == 'D'
		|| grid[(int)new_xy[0]][(int)new_xy[1]] == 'd')
		return ;
	get_new_xy(KEY_W, new_xy, game, 1);
	if (grid[(int)new_xy[0]][(int)new_xy[1]] == 'D')
		grid[(int)new_xy[0]][(int)new_xy[1]] = 'd';
	else if (grid[(int)new_xy[0]][(int)new_xy[1]] == 'd')
		grid[(int)new_xy[0]][(int)new_xy[1]] = 'D';
	get_new_xy(KEY_A, new_xy, game, 0.5);
	if (grid[(int)new_xy[0]][(int)new_xy[1]] == 'D')
		grid[(int)new_xy[0]][(int)new_xy[1]] = 'd';
	else if (grid[(int)new_xy[0]][(int)new_xy[1]] == 'd')
		grid[(int)new_xy[0]][(int)new_xy[1]] = 'D';
	get_new_xy(KEY_D, new_xy, game, 0.5);
	if (grid[(int)new_xy[0]][(int)new_xy[1]] == 'D')
		grid[(int)new_xy[0]][(int)new_xy[1]] = 'd';
	else if (grid[(int)new_xy[0]][(int)new_xy[1]] == 'd')
		grid[(int)new_xy[0]][(int)new_xy[1]] = 'D';
}
