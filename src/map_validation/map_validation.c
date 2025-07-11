/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caide-so <caide-so@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 16:57:30 by caide-so          #+#    #+#             */
/*   Updated: 2025/07/11 16:59:32 by caide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int		check_top_bot(t_map *map, char *row);
int		in(const char *s, char c);

int	validate_map(t_map *map)
{
	int	y;
	int	x;
	int	player_pos_count;

	y = 0;
	player_pos_count = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (!in("012NSEW", map->grid[y][x]))
				return (0);
			if (in("NSEW", map->grid[y][x]))
				player_pos_count++;
			if (player_pos_count > 1)
				return (0);
			if (y == 0 || y == map->height - 1)
				if (!check_top_bot(map, map->grid[y]))
					return (0);
			x++;
		}
		y++;
	}
	return (1);
}

int	check_top_bot(t_map *map, char *row)
{
	int	x;

	x = 0;
	while (x < map->width)
	{
		if (!in("1", row[x]))
			return (0);
		x++;
	}
	return (1);
}

// Checks if a character exists in a string
// 1. Iterates through s to find c
int	in(const char *s, char c)
{
	if (s == NULL)
		return (0);
	while (*s)
	{
		if (*s == c)
			return (1);
		s++;
	}
	return (0);
}
