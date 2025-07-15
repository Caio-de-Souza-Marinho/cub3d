/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcudos <marcudos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 14:44:34 by marcudos          #+#    #+#             */
/*   Updated: 2025/07/11 19:53:02 by marcudos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
int	set_color(t_color *target, char *value_str);
int	parse_rgb(t_color *color, char *value_str);

int	parse_color_line(t_config *cfg, char *line)
{
	char	*start;
	int		success;

	start = skip_spaces(line);
	if (*start == 'F')
	{
		start = skip_spaces(start + 1);
		success = set_color(&cfg->floor, start);
	}
	else if (*start == 'C')
	{
		start = skip_spaces(start + 1);
		success = set_color(&cfg->ceiling, start);
	}
	else
		return (0);
	return (success);
}

int	set_color(t_color *target, char *value_str)
{
	if (target->b != -1 || target->r != -1 || target->g != -1)
		return (error_msg("Color defined two times"));
	if (!parse_rgb(target, value_str))
		return (error_msg("Invalid RGB"));
	return (1);
}

void	set_values(int values[3])
{
	values[0] = -1;
	values[1] = -1;
	values[2] = -1;
}

int	parse_rgb(t_color *color, char *value_str)
{
	char	**parts;
	int	i;
	int	values[3];

	parts = ft_split(value_str, ',');
	if (!parts)
		return (0);
	set_values(values);
	i = 0;
	while (parts[i] && parts[i][0] != '\n')
	{
		if (i >= 3)
			return (free_array((void **) parts), 0);
		values[i] = ft_atoi(skip_spaces(parts[i]));
		if (values[i] < 0 || values[i] > 255)
			return (free_array((void **) parts), 0);
		i++;
	}
	color->r = values[0];
	color->g = values[1];
	color->b = values[2];
	free_array((void **) parts);
	return (1);
}
