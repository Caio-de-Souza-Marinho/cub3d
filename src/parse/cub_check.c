/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcudos <marcudos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 14:17:45 by marcudos          #+#    #+#             */
/*   Updated: 2025/07/10 14:55:08 by marcudos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	check_line_map(char *line)
{
	if (is_color_line(line) || is_texture_line(line))
		return (0);
	else if (is_empty_line(line))
		return (2);
	return (1);
}

int	check_final_file(int fd, char *line, t_list **map_lines, t_config *cfg)
{
	free(line);
	line = get_next_line(fd);
	while (line)
	{
		if (!is_empty_line(line))
		{
			free(line);
			ft_lstclear(map_lines, free);
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
	convert_list_to_matrix(map_lines, cfg);
	return (1);
}
