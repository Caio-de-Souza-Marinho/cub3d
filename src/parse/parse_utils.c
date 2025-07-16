/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcudos <marcudos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 17:59:10 by marcudos          #+#    #+#             */
/*   Updated: 2025/07/10 18:00:22 by marcudos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

char	*skip_spaces(char *str)
{
	int	i;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	return (&str[i]);
}

int	check_line_map(char *line)
{
	if (is_color_line(line) || is_texture_line(line))
		return (0);
	else if (is_empty_line(line))
		return (2);
	return (1);
}

int	check_final_file(int fd, char *line, t_list **map_l, t_config *cfg)
{
	free(line);
	line = get_next_line(fd);
	while (line)
	{
		if (!is_empty_line(line))
		{
			free(line);
			ft_lstclear(map_l, free);
			line = get_next_line(fd);
			while (line)
			{
				free(line);
				line = get_next_line(fd);
			}
			close(fd);
			return (error_msg("Find line after map"));
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	convert_list_to_matrix(map_l, cfg);
	ft_lstclear(map_l, free);
	return (1);
}
