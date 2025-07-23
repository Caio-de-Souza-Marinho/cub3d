/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caide-so <caide-so@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 19:21:33 by caide-so          #+#    #+#             */
/*   Updated: 2025/07/22 22:37:25 by caide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	check_errors(char *arg, t_game *game);

int	main(int argc, char **argv)
{
	t_game	*game;

	if (argc != 2 || ft_strcmp(&argv[1][ft_strlen(argv[1]) - 4], ".cub") != 0)
		return (printf("Not a .cub file\n"), 1);
	game = init_empty_game();
	if (!check_errors(argv[1], game))
	{
		free_game(game);
		return (EXIT_FAILURE);
	}
	print_config(game->cfg);
	gettimeofday(&game->last_frame_time, NULL);
	mlx_loop_hook(game->mlx, &render_frame, game);
	mlx_hook(game->win, 17, 0, exit_game, game);
	mlx_hook(game->win, 2, 1L << 0, handle_key_press, game);
	mlx_hook(game->win, 3, 1L << 1, handle_key_release, game);
	mlx_hook(game->win, 6, 1L << 6, handle_mouse_move, game);
	mlx_loop(game->mlx);
	return (EXIT_SUCCESS);
}

int	check_errors(char *arg, t_game *game)
{
	if (!game || !parse_cub(arg, game->cfg)
		|| check_cub_complete(game->cfg))
		return (0);
	if (init_game_graphics(game))
		return (0);
	if (load_all_textures(game))
		return (0);
	if (init_sprite(game))
		return (0);
	return (1);
}

int	exit_game(t_game *game)
{
	free_game(game);
	exit(0);
}
