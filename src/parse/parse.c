/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcudos <marcudos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:10:31 by marcudos          #+#    #+#             */
/*   Updated: 2025/07/09 20:17:33 by marcudos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
void	get_texture(t_config *cfg, char *line);
void	get_color(t_config *cfg, char *line);

int	parse_cub(char *filename, t_config *cfg)
{
	char	*line;
	int	fd;
	int	in_map;
	t_list	*map_lines;

	fd = open(filename, O_RDONLY);
	line = get_next_line(fd);
	map_lines = NULL;
	in_map = 0;
	(void) cfg;
	while (line)
	{
		if (in_map || is_map_line(line))
		{
			in_map = 1;
			ft_lstadd_back(&map_lines, ft_lstnew(line));
		}
		else if (is_texture_line(line))
			get_texture(cfg, line);
		else if (is_color_line(line))
			get_color(cfg, line);
		if (line)
			free(line);
		line = get_next_line(fd);
	}
	return (1);
}

void	get_texture(t_config *cfg, char *line)
{
}

void	get_color(t_config *cfg, char *line)
{}
