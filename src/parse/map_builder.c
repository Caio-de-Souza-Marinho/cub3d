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

// Adds a copy of the given line to the end of the map lines linked list
// 1. Duplicates the input line string
// 2. Creates a new list node with the duplicated string
// 3. Adds new node to the end of the list
// 4. Returns 1 on success, 0 on memory allocation failure
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

// Allocates a 2D char matrix with given width and height
// 1. Allocates array of pointers for rows plus NULL terminator
// 2. Allocates each row with space for width + null terminator
// 3. Returns pointer to allocated matrix or NULL on failure
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

// Copies map lines from linked list into allocated matrix
// 1. Iterates each line in list
// 2. Copies characters, replacing spaces with '2'
// 3. Pads remaining columns with '2'
// 4. Null-terminates each matrix row
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

// Converts linked list of map lines into a matrix and updates config
// 1. Counts height and max width from list contents
// 2. Allocates matrix with determined size
// 3. Copies list lines into matrix with make_matrix()
// 4. Updates cfg map grid, width, and height
// 5. Finds and sets player start position
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
