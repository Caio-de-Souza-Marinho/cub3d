/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caide-so <caide-so@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 16:57:30 by caide-so          #+#    #+#             */
/*   Updated: 2025/07/18 17:20:49 by marcudos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int		validate_chars(t_map *map);
int		in(const char *s, char c);
int		flood_fill(char **map, int y, int x, int height);

// Validates map and player position using flood fill and other validations.
// 1. Returns 0 if invalid characters or no player.
// 2. Copies map and checks if flood fill reaches boundaries.
// 3. Frees copy and returns 1 if map is closed.
int	validate_map(t_map *map, t_player *player)
{
	char	**copy;

	if (!validate_chars(map))
		return (0);
	if (player->x < 0 || player->y < 0)
		return (0);
	copy = copy_map(map);
	if (!copy)
		return (0);
	if (!flood_fill(copy, player->y, player->x, map->height))
	{
		free_map_copy(copy, map->height);
		return (0);
	}
	free_map_copy(copy, map->height);
	return (1);
}

// Validates map characters and player spawn count
// 1. Iterates each tile in map grid.
// 2. Returns 0 if tile is not in allowed set "012DCNSEW"
// 3. Counts player spawns ("NSEW"), must be exactly 1.
int	validate_chars(t_map *map)
{
	int	y;
	int	x;
	int	count;

	y = 0;
	count = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (!in("012DCNSEW", map->grid[y][x]))
				return (0);
			if (in("NSEW", map->grid[y][x]))
				count++;
			x++;
		}
		y++;
	}
	return (count == 1);
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

// Performs recursive flood fill to validate map closure.
// 1. Returns 0 if out of bounds or open edge.
// 2. Marks visited tiles with 'F'.
// 3. Recursively checks up, down, left, right.
int	flood_fill(char **map, int y, int x, int height)
{
	if (y < 0 || x < 0 || !map[y] || x >= (int)ft_strlen(map[y]))
		return (0);
	if (!in("02DCNSEW", map[y][x]))
		return (1);
	map[y][x] = 'F';
	if (!flood_fill(map, y - 1, x, height))
		return (0);
	if (!flood_fill(map, y + 1, x, height))
		return (0);
	if (!flood_fill(map, y, x - 1, height))
		return (0);
	if (!flood_fill(map, y, x + 1, height))
		return (0);
	return (1);
}
