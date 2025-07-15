/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcudos <marcudos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 14:17:45 by marcudos          #+#    #+#             */
/*   Updated: 2025/07/11 19:43:00 by marcudos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	check_colors_cub(t_config *cfg)
{
	int	status;

	status = 1;
	if (cfg->floor.r == -1 || cfg->floor.g == -1
		|| cfg->floor.b == -1)
	{
		status = 0;
		printf("Floor collor missing\n");
	}
	if (cfg->ceiling.r == -1 || cfg->ceiling.g == -1
		|| cfg->ceiling.b == -1)
	{
		status = 0;
		printf("Ceiling collor missing\n");
	}
	return (status);
}

int	check_cub_complete(t_config *cfg)
{
	if (!check_colors_cub(cfg))
		return (0);
	return (1);
}
