/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcudos <marcudos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 14:45:35 by marcudos          #+#    #+#             */
/*   Updated: 2025/07/11 19:53:07 by marcudos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	set_texture(char **target, char **values);

int	parse_texture_line(t_config *cfg, char *line)
{
	char	**values;

	values = ft_split(line, ' ');
	if (!values)
		return (0);
	if (ft_strcmp(values[0], "NO") == 0)
		return (set_texture(&cfg->texture.no, values));
	else if (ft_strcmp(values[0], "SO") == 0)
		return (set_texture(&cfg->texture.so, values));
	else if (ft_strcmp(values[0], "WE") == 0)
		return (set_texture(&cfg->texture.we, values));
	else if (ft_strcmp(values[0], "EA") == 0)
		return (set_texture(&cfg->texture.ea, values));
	return (0);
}

int	set_texture(char **target, char **values)
{
	// int	fd;

	if (*target)
	{
		free_array((void **) values);
		return (error_msg("double Texture"));
	}
	if (!values[1])
	{
		free_array((void **) values);
		return (error_msg("Missing texture path"));
	}
	values[1][ft_strlen(values[1]) - 1] = '\0';
	// fd = open(values[1], O_RDONLY);
	// if (fd < 0)
	// {
	// 	free_array((void **) values);
	// 	return (error_msg("Error to open file"));
	// }
	// close(fd);
	*target = ft_strdup(values[1]);
	free_array((void **) values);
	return (1);
}
