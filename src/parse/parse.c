/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcudos <marcudos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:10:31 by marcudos          #+#    #+#             */
/*   Updated: 2025/07/10 18:34:06 by marcudos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
int	handle_line(char *line, t_config *cfg, t_list **map_lines, int *in_map);

int	parse_cub(char *filename, t_config *cfg)
{
	char	*line;
	int	fd;
	int	in_map;
	int	h_line;
	t_list	*map_lines;

	fd = open(filename, O_RDONLY);
	map_lines = NULL;
	in_map = 0;
	line = get_next_line(fd);
	while (line)
	{
		h_line = handle_line(line, cfg, &map_lines, &in_map);
		if (h_line == 0)
			return (free(line), 0);
		if (h_line == 2)
			return (check_final_file(fd, line, &map_lines, cfg));
		free(line);
		line = get_next_line(fd);
	}
	convert_list_to_matrix(&map_lines, cfg);
	return (1);
}

int	handle_line(char *line, t_config *cfg, t_list **map_lines, int *in_map)
{
	int	map_status;

	if (*in_map || is_map_line(line))
	{
		map_status = check_line_map(line);
		if (map_status == 0)
			return (error_msg("Invalid line in map"));
		if (map_status == 2)
			return (2);
		*in_map = 1;
		return (add_map_line(map_lines, line)
			|| error_msg("Error to save map line"));
	}
	else if (is_texture_line(line))
		return (parse_texture_line(cfg, line)
			|| error_msg("Invalid Texture"));
	else if (is_color_line(line))
		return (parse_color_line(cfg, line)
			|| error_msg("Invalid Color"));
	else if (is_empty_line(line))
		return (1);
	return (error_msg("Invalid line in file .cub"));
}
