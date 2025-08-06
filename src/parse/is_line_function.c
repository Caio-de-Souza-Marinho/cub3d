/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_line_function.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcudos <marcudos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:44:22 by marcudos          #+#    #+#             */
/*   Updated: 2025/07/18 17:01:09 by marcudos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// Checks if a line defines a texture (NO, SO, WE, EA)
// 1. Skips whitespace characters
// 2. Checks for texture identifiers "NO", "SO", "WE", or "EA"
// 3. Returns 1 if texture line, 0 otherwise
int	is_texture_line(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (ft_isspace(line[i]))
			continue ;
		if (line[i] == 'N' && line[i + 1] == 'O')
			return (1);
		else if (line[i] == 'S' && line[i + 1] == 'O')
			return (1);
		else if (line[i] == 'W' && line[i + 1] == 'E')
			return (1);
		else if (line[i] == 'E' && line[i + 1] == 'A')
			return (1);
		else
			return (0);
	}
	return (0);
}

// Checks if a line defines a color (floor 'F' or ceiling 'C')
// 1. Skips whitespace characters
// 2. Checks if first non-space char is 'F' or 'C'
// 3. Returns 1 if color line, 0 otherwise
int	is_color_line(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (ft_isspace(line[i]))
			continue ;
		if (line[i] == 'F')
			return (1);
		else if (line[i] == 'C')
			return (1);
		else
			return (0);
	}
	return (0);
}

// Checks if a line is part of the map layout
// 1. Skips leading whitespace
// 2. Returns 0 if line is empty after spaces
// 3. Scans remaining characters checking for valid map chars
// (1,0,space,N,S,W,E,D,d)
// 4. Returns 1 if valid map line, 0 otherwise
int	is_map_line(char *line)
{
	int	i;
	int	valid;

	i = -1;
	while (ft_isspace(line[++i]))
		;
	if (!line[i])
		return (0);
	valid = 0;
	while (line[++i])
	{
		if (ft_isspace(line[i]))
			continue ;
		else
			valid = 1;
		if (line[i] != '1' && line[i] != '0' && line[i] != ' '
			&& line[i] != 'N' && line[i] != 'S'
			&& line[i] != 'W' && line[i] != 'E'
			&& line[i] != 'D' && line[i] != 'd')
			return (0);
	}
	return (valid);
}

// Checks if a line is empty or contains only whitespace
// 1. Returns 0 if line is NULL
// 2. Returns 0 if any non-whitespace character found
// 3. Returns 1 if line is empty or all whitespace
int	is_empty_line(char *line)
{
	int	i;

	i = -1;
	if (!line)
		return (0);
	while (line[++i])
	{
		if (!ft_isspace(line[i]))
			return (0);
	}
	return (1);
}
