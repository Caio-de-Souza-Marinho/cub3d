/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcudos <marcudos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 18:38:04 by marcudos          #+#    #+#             */
/*   Updated: 2025/07/15 22:06:28 by marcudos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include <stdio.h>

void	print_details(t_cfg *cfg)
{
	printf(BLUE "Textures:\n");
	printf("NO: %s\n", cfg->texture.no.path);
	printf("SO: %s\n", cfg->texture.so.path);
	printf("WE: %s\n", cfg->texture.we.path);
	printf("EA: %s\n", cfg->texture.ea.path);
	printf("\nColors:\n");
	printf("Floor: R = %d, G = %d, ", cfg->floor.r, cfg->floor.g);
	printf("B = %d\n", cfg->floor.b);
	printf("Ceiling: R = %d, G = %d, ", cfg->ceiling.r, cfg->ceiling.g);
	printf("B = %d\n" RESET, cfg->ceiling.b);
}

void	print_player(t_cfg *cfg)
{
	printf(BLUE "\nPlayer:\n");
	printf("X: %f\n", cfg->player.x);
	printf("Y: %f\n", cfg->player.y);
	printf("Dir: %c\n" RESET, cfg->player.dir);
}

void	print_config(t_cfg *cfg)
{
	int	i;
	int	j;

	print_details(cfg);
	print_player(cfg);
	printf(GREEN "\nMap:\n" RESET);
	i = -1;
	while (++i < cfg->map.height)
	{
		j = -1;
		while (++j < cfg->map.width)
		{
			if (cfg->map.grid[i][j] == '0')
				printf(BLUE "%c" RESET, cfg->map.grid[i][j]);
			else if (cfg->map.grid[i][j] == '1')
				printf(GREEN "%c" RESET, cfg->map.grid[i][j]);
			else if (cfg->map.grid[i][j] == '2')
				printf(RED "%c" RESET, cfg->map.grid[i][j]);
			else
				printf(BYELLOW "%c" RESET, cfg->map.grid[i][j]);
		}
		printf("\n");
	}
	printf("width: %d, height: %d\n", cfg->map.width, cfg->map.height);
}
