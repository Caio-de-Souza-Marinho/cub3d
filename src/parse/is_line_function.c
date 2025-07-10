/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_line_function.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcudos <marcudos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:44:22 by marcudos          #+#    #+#             */
/*   Updated: 2025/07/10 14:05:11 by marcudos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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
			&& line[i] != 'W' && line[i] != 'E')
			return (0);
	}
	return (valid);
}

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
