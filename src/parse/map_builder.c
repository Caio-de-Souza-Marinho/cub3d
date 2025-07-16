/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_builder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcudos <marcudos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 14:49:02 by marcudos          #+#    #+#             */
/*   Updated: 2025/07/15 22:11:46 by marcudos         ###   ########.fr       */
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

char	**alloc_matrix(int width, int height)
{
	char	**matrix;
	int		i;

	matrix = (char **) malloc(sizeof(char *) * (height + 1));
	if (!matrix)
		return (NULL);
	i = 0;
	while (i < height)
	{
		matrix[i] = (char *) malloc(sizeof(char) * (width + 1));
		if (!matrix[i])
			return (NULL);
		i++;
	}
	matrix[i] = NULL;
	return (matrix);
}

void	make_matrix(t_list **map_lines, char **matrix, int width)
{
	t_list	*tmp;
	char	*str;
	int		line;
	int		i;

	tmp = *map_lines;
	line = 0;
	while (tmp)
	{
		i = 0;
		str = tmp->content;
		while (str[i] != '\0' && str[i] != '\n')
		{
			if (str[i] == ' ')
				matrix[line][i] = '2';
			else
				matrix[line][i] = str[i];
			i++;
		}
		while (i < width)
			matrix[line][i++] = '2';
		matrix[line][i] = '\0';
		line++;
		tmp = tmp->next;
	}
}

void	convert_list_to_matrix(t_list **map_lines, t_cfg *cfg)
{
	t_list	*tmp;
	char	**matrix;
	int		width;
	int		height;

	width = 0;
	height = 0;
	tmp = *map_lines;
	matrix = NULL;
	while (tmp)
	{
		height++;
		if ((int) ft_strlen(tmp->content) - 1 > width)
			width = ft_strlen(tmp->content) - 1;
		tmp = tmp->next;
	}
	matrix = alloc_matrix(width, height);
	make_matrix(map_lines, matrix, width);
	cfg->map.grid = matrix;
	cfg->map.width = width;
	cfg->map.height = height;
	get_player_position(cfg);
}
