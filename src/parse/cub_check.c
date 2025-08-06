/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcudos <marcudos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 14:17:45 by marcudos          #+#    #+#             */
/*   Updated: 2025/07/15 22:16:33 by marcudos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// Checks if floor and ceiling colors are set in configuration.
// 1. Checks if any RGB component of floor color is unset (-1).
// 2. Checks if any RGB component of ceiling color is unset (-1).
// 3. Prints message depending on missing colors (floor, ceiling, or both).
// 4. Returns status code representing missing colors (0 = none, 1 = floor,
// 2 = ceiling, 3 = both).
int	check_colors_cub(t_cfg *cfg)
{
	int	status;

	status = 0;
	if (cfg->floor.r == -1 || cfg->floor.g == -1
		|| cfg->floor.b == -1)
		status += 1;
	if (cfg->ceiling.r == -1 || cfg->ceiling.g == -1
		|| cfg->ceiling.b == -1)
		status += 2;
	if (status == 1)
		printf("Missing floor color\n");
	else if (status == 2)
		printf("Missing ceiling color\n");
	else if (status == 3)
		printf("Misisng floor and ceiling colors\n");
	return (status);
}

// Checks if texture file paths have the correct .xpm extension
// 1. Extracts texture file paths for north, south, east and west walls.
// 2. Compares last 4 chars of each path with ".xpm".
// 3. Returns 1 if any texture file does not have .xpm extension, 0 otherwise.
int	check_type_f(t_cfg *cfg)
{
	char	*fl[4];

	fl[0] = cfg->texture.no.path;
	fl[1] = cfg->texture.so.path;
	fl[2] = cfg->texture.ea.path;
	fl[3] = cfg->texture.we.path;
	if (ft_strcmp(&fl[0][ft_strlen(fl[0]) - 4], ".xpm") != 0)
		return (1);
	if (ft_strcmp(&fl[1][ft_strlen(fl[1]) - 4], ".xpm") != 0)
		return (1);
	if (ft_strcmp(&fl[2][ft_strlen(fl[2]) - 4], ".xpm") != 0)
		return (1);
	if (ft_strcmp(&fl[3][ft_strlen(fl[3]) - 4], ".xpm") != 0)
		return (1);
	return (0);
}

// Validates that texture paths are set and texture files can be opened.
// 1. Checks if any wall texture path is missing (NULL).
// 2. Checks that all texture files have .xpm extension via check_type().
// 3. Opens each texture file for reading to verify accessibility.
// 4. Counts how many texture files failed to open and closes opened files.
// 5. Prints error message if any files can't be opened.
// 6. Returns number of inaccessible texture files or 0 if all succeed.
int	check_texture_cub(t_cfg *cfg)
{
	int	fd[4];
	int	i;
	int	status;

	if (!cfg->texture.no.path || !cfg->texture.so.path
		|| !cfg->texture.ea.path || !cfg->texture.we.path)
		return (printf("Missing texture\n"), 1);
	if (check_type_f(cfg))
		return (printf("Texture file must have .xpm extension\n"), 1);
	fd[0] = open(cfg->texture.no.path, O_RDONLY);
	fd[1] = open(cfg->texture.so.path, O_RDONLY);
	fd[2] = open(cfg->texture.ea.path, O_RDONLY);
	fd[3] = open(cfg->texture.we.path, O_RDONLY);
	i = -1;
	status = 0;
	while (++i < 4)
	{
		if (fd[i] <= 0)
			status++;
		else
			close(fd[i]);
	}
	if (status)
		printf("Can't open %d texture files\n", status);
	return (status);
}

// Validates the map size in configuration.
// 1. Checks if map dimensions are zero (no map).
// 2. Checks if map dimensions are too small (<= 3x3).
// 3. Prints an error message if map is missing or too small.
// 4. Returns status code indicating map problem (0 = valid, 1 = missing,
// 2 = too small).
int	check_map_cub(t_cfg *cfg)
{
	int	status;

	status = 0;
	if (cfg->map.height == 0 && cfg->map.width == 0)
		status += 1;
	else if (cfg->map.height <= 3 && cfg->map.width <= 3)
		status += 2;
	if (status == 1)
		printf("Missing map\n");
	else if (status == 2)
		printf("Map too small\n");
	return (status);
}

// Performs comprehensive validation of the parsed configuration
// 1. Checks for valid floor and ceiling colors via check_colors_cub()
// 2. Checks map presence and size via check_map_cub()
// 3. Checks textures via check_texture_cub()
// 4. Validates map layout and player start position via validate_map()
// 5. Prints error message if map validation fails
// 6. Returns total status code indicating any errors detected
int	check_cub_complete(t_cfg *cfg)
{
	int	status;

	status = 0;
	status += check_colors_cub(cfg);
	status += check_map_cub(cfg);
	status += check_texture_cub(cfg);
	if (!validate_map(&cfg->map, &cfg->player))
	{
		status++;
		printf("Invalid map\n");
	}
	return (status);
}
