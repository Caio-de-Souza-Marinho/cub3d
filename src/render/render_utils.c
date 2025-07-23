/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caide-so <caide-so@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 22:40:45 by caide-so          #+#    #+#             */
/*   Updated: 2025/07/22 22:41:36 by caide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

double	get_delta_time(t_game *game)
{
	struct timeval	current;
	double			delta;

	gettimeofday(&current, NULL);
	delta = (current.tv_sec - game->last_frame_time.tv_sec)
		+ (current.tv_usec - game->last_frame_time.tv_usec) / 1e6;
	game->last_frame_time = current;
	return (delta);
}
