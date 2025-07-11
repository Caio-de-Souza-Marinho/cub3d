/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caide-so <caide-so@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 19:21:33 by caide-so          #+#    #+#             */
/*   Updated: 2025/07/11 19:37:19 by marcudos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <stdlib.h>

int	main(int argc, char **argv)
{
	t_config	*cfg;

	(void)argc;
	(void)argv;
	cfg = init_config();
	if (!parse_cub(argv[1], cfg))
	{
		free(cfg);
		printf("Invalid Map");
		return (1);
	}
	// print_config(cfg);
	free_config(cfg);
	return (0);
}
