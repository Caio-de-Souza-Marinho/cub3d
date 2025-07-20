/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcudos <marcudos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 14:45:35 by marcudos          #+#    #+#             */
/*   Updated: 2025/07/15 22:36:05 by marcudos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	set_texture(char **target, char **values);

int	parse_texture_line(t_cfg *cfg, char *line)
{
	char	**values;

	values = ft_split(line, ' ');
	if (!values)
		return (0);
	if (ft_strcmp(values[0], "NO") == 0)
		return (set_texture(&cfg->texture.no.path, values));
	else if (ft_strcmp(values[0], "SO") == 0)
		return (set_texture(&cfg->texture.so.path, values));
	else if (ft_strcmp(values[0], "WE") == 0)
		return (set_texture(&cfg->texture.we.path, values));
	else if (ft_strcmp(values[0], "EA") == 0)
		return (set_texture(&cfg->texture.ea.path, values));
	return (0);
}

int	set_texture(char **target, char **values)
{
	if (*target)
	{
		free_array((void **) values);
		return (error_msg("Double texture"));
	}
	if (!values[1])
	{
		free_array((void **) values);
		return (error_msg("Missing texture path"));
	}
	if (values[1][ft_strlen(values[1]) - 1] == '\n')
		values[1][ft_strlen(values[1]) - 1] = '\0';
	*target = ft_strdup(values[1]);
	free_array((void **) values);
	return (1);
}
