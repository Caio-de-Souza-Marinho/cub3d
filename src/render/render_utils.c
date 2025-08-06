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

// Calculates time difference since last frame.
// 1. Gets current time with gettimeofday.
// 2. Calculates time delta in seconds (including microseconds).
// 3. Updates game's last_frame_time to current.
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
