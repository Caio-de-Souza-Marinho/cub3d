/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_collector.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcudos <marcudos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 14:49:02 by marcudos          #+#    #+#             */
/*   Updated: 2025/07/10 14:57:24 by marcudos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	add_map_line(t_list **map_lines, char *line)
{
	char	*copy;
	t_list	*new;

	copy = ft_strdup(line);
	if (!copy)
		return (0);
	new = ft_lstnew(copy);
	if (!new)
	{
		free(copy);
		return (0);
	}
	ft_lstadd_back(map_lines, new);
	return (1);
}
