/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcudos <marcudos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:10:31 by marcudos          #+#    #+#             */
/*   Updated: 2025/07/11 19:52:58 by marcudos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	handle_line(char *line, t_cfg *cfg, t_list **map_lines, int *in_map);

// Parses a .cub configuration file into the cfg struct.
// 1. Opens the file and reads it line-by-line.
// 2. Sends each line to handle_line().
// 3. Builds a list of map lines, then converts to 2D array.
int	parse_cub(char *filename, t_cfg *cfg)
{
	char	*line;
	int		fd;
	int		in_map;
	int		h_line;
	t_list	*map_lines;

	fd = open(filename, O_RDONLY);
	map_lines = NULL;
	in_map = 0;
	line = get_next_line(fd);
	while (line)
	{
		h_line = handle_line(line, cfg, &map_lines, &in_map);
		if (h_line == 0)
			return (close(fd), free(line), free_gnl(fd), 0);
		if (h_line == 2)
			return (check_final_file(fd, line, &map_lines, cfg));
		free(line);
		line = get_next_line(fd);
	}
	convert_list_to_matrix(&map_lines, cfg);
	ft_lstclear(&map_lines, free);
	return (close(fd), 1);
}

// Handles a single ilne from the .cub file.
// 1. Parses textures, colors, or map lines.
// 2. Tracks when map parsing starts via *in_map.
// 3. Returns 2 if map ended, 0 on error, 1 on success.
int	handle_line(char *line, t_cfg *cfg, t_list **map_lines, int *in_map)
{
	int	map_status;

	if (*in_map || is_map_line(line))
	{
		map_status = check_line_map(line);
		if (map_status == 0)
			return (error_msg("Invalid line in the map"));
		if (map_status == 2)
			return (2);
		*in_map = 1;
		return (add_map_line(map_lines, line)
			|| error_msg("Error to save map line"));
	}
	else if (is_texture_line(line))
		return (parse_texture_line(cfg, line)
			|| 0);
	else if (is_color_line(line))
		return (parse_color_line(cfg, line)
			|| 0);
	else if (is_empty_line(line))
		return (1);
	return (error_msg("Invalid line in the .cub file"));
}
