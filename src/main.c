/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caide-so <caide-so@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 19:21:33 by caide-so          #+#    #+#             */
/*   Updated: 2025/07/09 17:42:48 by marcudos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <stdlib.h>

int	main(int argc, char **argv)
{
	t_config	*cfg;

	(void)argc;
	(void)argv;
	printf("oi cub3d\n");
	cfg = (t_config *) malloc(sizeof(t_config));
	if (!parse_cub(argv[1], cfg))
	{
		printf("Invalid Map");
		return (1);
	}
	return (0);
}
