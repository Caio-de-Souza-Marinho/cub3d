/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcudos <marcudos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 18:38:04 by marcudos          #+#    #+#             */
/*   Updated: 2025/07/11 18:52:52 by marcudos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	print_config(t_config *cfg)
{
	int	i;
	int	j;

	printf("Textures:\n");
	printf("NO: %s\n", cfg->texture.no);
	printf("SO: %s\n", cfg->texture.so);
	printf("WE: %s\n", cfg->texture.we);
	printf("EA: %s\n", cfg->texture.ea);
	printf("\nColors:\n");
	printf("Floor: R = %d, G = %d, B = %d\n", cfg->floor.r, cfg->floor.g, cfg->floor.b);
	printf("Ceiling: R = %d, G = %d, B = %d\n", cfg->ceiling.r, cfg->ceiling.g, cfg->ceiling.b);
	printf("\nMap:\n");
	i = 0;
	while (i < cfg->map.height)
	{
		printf("[ ");
		j = 0;
		while (j < cfg->map.width)
		{
			if (j == cfg->map.width - 1)
				printf("%c", cfg->map.grid[i][j]);
			else
				printf("%c, ", cfg->map.grid[i][j]);
			j++;
		}
		printf(" ]\n");
		i++;
	}
	printf("width: %d, height: %d\n", cfg->map.width, cfg->map.height);
}
