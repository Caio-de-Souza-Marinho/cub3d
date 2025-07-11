/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caide-so <caide-so@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 19:21:33 by caide-so          #+#    #+#             */
/*   Updated: 2025/07/11 16:59:25 by caide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

char	**create_test_map(int *height);
void	free_map(t_config *config);

int	main(void)
{
	t_config	config;

	config.map.grid = create_test_map(&config.map.height);
	config.map.width = 6;
	config.player.x = 4;
	config.player.y = 2;
	config.player.dir = 'N';
	if (validate_map(&config.map))
		printf("Map is valid\n");
	else
		printf("Map is invalid\n");
	free_map(&config);
	return (0);
}

char	**create_test_map(int *height)
{
	char	**grid;

	grid = (char **)malloc(sizeof(char *) * 6);
	if (!grid)
		return (NULL);
	grid[0] = ft_strdup("111111");
	grid[1] = ft_strdup("100001");
	grid[2] = ft_strdup("1000N1");
	grid[3] = ft_strdup("100001");
	grid[4] = ft_strdup("111111");
	grid[5] = NULL;
	*height = 5;
	return (grid);
}

void	free_map(t_config *config)
{
	int	i;

	i = 0;
	while (i < config->map.height)
	{
		free(config->map.grid[i]);
		i++;
	}
	free(config->map.grid);
}
