/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcudos <marcudos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 14:17:45 by marcudos          #+#    #+#             */
/*   Updated: 2025/07/15 22:16:33 by marcudos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	check_colors_cub(t_config *cfg)
{
	int	status;

	status = 0;
	if (cfg->floor.r == -1 || cfg->floor.g == -1
		|| cfg->floor.b == -1)
		status += 1;
	if (cfg->ceiling.r == -1 || cfg->ceiling.g == -1
		|| cfg->ceiling.b == -1)
		status += 2;
	if (status == 1)
		printf("Floor collor missing\n");
	else if (status == 2)
		printf("Ceiling collor missing\n");
	else if (status == 3)
		printf("Floor and Ceiling collors missing\n");
	return (status);
}

int	check_type_f(t_config *cfg)
{
	char	*fl[4];

	fl[0] = cfg->texture.no;
	fl[1] = cfg->texture.so;
	fl[2] = cfg->texture.ea;
	fl[3] = cfg->texture.we;
	if (ft_strcmp(&fl[0][ft_strlen(fl[0]) - 4], ".xpm") != 0)
		return (1);
	if (ft_strcmp(&fl[1][ft_strlen(fl[1]) - 4], ".xpm") != 0)
		return (1);
	if (ft_strcmp(&fl[2][ft_strlen(fl[2]) - 4], ".xpm") != 0)
		return (1);
	if (ft_strcmp(&fl[3][ft_strlen(fl[3]) - 4], ".xpm") != 0)
		return (1);
	return (0);
}

int	check_texture_cub(t_config *cfg)
{
	int	fd[4];
	int	i;
	int	status;

	if (!cfg->texture.no || !cfg->texture.so
		|| !cfg->texture.ea || !cfg->texture.we)
		return (printf("Missing texture\n"), 1);
	if (check_type_f(cfg))
		return (printf("Invalid texture type file\n"), 1);
	fd[0] = open(cfg->texture.no, O_RDONLY);
	fd[1] = open(cfg->texture.so, O_RDONLY);
	fd[2] = open(cfg->texture.ea, O_RDONLY);
	fd[3] = open(cfg->texture.we, O_RDONLY);
	i = -1;
	status = 0;
	while (++i < 4)
	{
		if (fd[i] <= 0)
			status++;
		else
			close(fd[i]);
	}
	if (status)
		printf("Can't open %d textures files\n", status);
	return (status);
}

int	check_map_cub(t_config *cfg)
{
	int	status;

	status = 0;
	if (cfg->map.height == 0 && cfg->map.width == 0)
		status += 1;
	else if (cfg->map.height <= 3 && cfg->map.width <= 3)
		status += 2;
	if (status == 1)
		printf("Missing map\n");
	else if (status == 2)
		printf("Map too small\n");
	return (status);
}

int	check_cub_complete(t_config *cfg)
{
	int	status;

	status = 0;
	status += check_colors_cub(cfg);
	status += check_map_cub(cfg);
	status += check_texture_cub(cfg);
	if (!validate_map(&cfg->map, &cfg->player))
	{
		status++;
		printf("Invalid map\n");
	}
	return (status);
}
