/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caide-so <caide-so@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 19:21:33 by caide-so          #+#    #+#             */
/*   Updated: 2025/07/17 21:51:02 by caide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	main(int argc, char **argv)
{
	t_game	*game;

	(void)argc;
	if (ft_strcmp(&argv[1][ft_strlen(argv[1]) - 4], ".cub") != 0)
		return (printf("Not a .cub file\n"), 1);
	game = init_game();
	if (!parse_cub(argv[1], game->cfg) || check_cub_complete(game->cfg))
	{
		free_config(game->cfg);
		return (1);
	}
	print_config(game->cfg);
	mlx_loop_hook(game->mlx, &render_frame, game);
	mlx_loop(game->mlx);
	free_config(game->cfg);
	return (0);
}
