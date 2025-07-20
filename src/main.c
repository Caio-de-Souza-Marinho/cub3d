/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caide-so <caide-so@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 19:21:33 by caide-so          #+#    #+#             */
/*   Updated: 2025/07/17 22:39:21 by caide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	handle_key(int keycode, t_game *game);
int	exit_game(t_game *game);

int	main(int argc, char **argv)
{
	t_game	*game;

	(void)argc;
	if (ft_strcmp(&argv[1][ft_strlen(argv[1]) - 4], ".cub") != 0)
		return (printf("Not a .cub file\n"), 1);
	game = init_game();
	if (!parse_cub(argv[1], game->cfg) || check_cub_complete(game->cfg)
		|| load_all_textures(game))
	{
		free_game(game);
		return (1);
	}
	print_config(game->cfg);
	mlx_loop_hook(game->mlx, &render_frame, game);
	mlx_hook(game->win, 17, 0, exit_game, game);
	mlx_hook(game->win, 2, 1L << 0, handle_key, game);
	mlx_loop(game->mlx);
	return (0);
}

int	exit_game(t_game *game)
{
	free_game(game);
	exit(0);
}

void	rotate_player(int keycode, t_game *game, double angle)
{
	double	tmp_dx;
	double	tmp_px;
	double	dy;
	double	py;

	tmp_dx = game->cfg->player.dir_x;
	dy = game->cfg->player.dir_y;
	tmp_px = game->cfg->player.plane_x;
	py = game->cfg->player.plane_y;
	if (keycode == KEY_LEFT)
	{
		game->cfg->player.dir_x = tmp_dx * cos(-angle) - dy * sin(-angle);
		game->cfg->player.dir_y = tmp_dx * sin(-angle) + dy * cos(-angle);
		game->cfg->player.plane_x = tmp_px * cos(-angle) - py * sin(-angle);
		game->cfg->player.plane_y = tmp_px * sin(-angle) + py * cos(-angle);
	}
	else if (keycode == KEY_RIGHT)
	{
		game->cfg->player.dir_x = tmp_dx * cos(angle) - dy * sin(angle);
		game->cfg->player.dir_y = tmp_dx * sin(angle) + dy * cos(angle);
		game->cfg->player.plane_x = tmp_px * cos(angle) - py * sin(angle);
		game->cfg->player.plane_y = tmp_px * sin(angle) + py * cos(angle);
	}
}

int	handle_key(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		exit_game(game);
	else if (keycode == KEY_LEFT || keycode == KEY_RIGHT)
		rotate_player(keycode, game, 0.05);
	return (0);
}
