/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caide-so <caide-so@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 15:13:02 by caide-so          #+#    #+#             */
/*   Updated: 2025/07/02 23:32:50 by caide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

// Prints a single character with width formatting
// 1. Applies left-justified or right-aligned padding
// 2. Writes the character to the buffer
//
// Note: Handles %c and %% specifiers
void	printf_char(t_data *data, int c)
{
	int	width;

	width = data->format.width_value;
	if (width > 1 && data->format.specifier != '%')
	{
		if (data->format.left_justified)
		{
			putchar_buf_n((char)c, 1, data);
			putchar_buf_n(' ', width - 1, data);
		}
		else
		{
			putchar_buf_n(' ', width - 1, data);
			putchar_buf_n((char)c, 1, data);
		}
	}
	else
		putchar_buf_n((char)c, 1, data);
}
