/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caide-so <caide-so@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 02:34:51 by caide-so          #+#    #+#             */
/*   Updated: 2025/07/02 23:32:36 by caide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

static void	set_str_padding(t_data *data, int print_len);
static int	get_print_len(t_data *data, int str_len, int is_null);
static void	handle_null_str(t_data *data, char **s, int *is_null);

// Prints a string with formatting (width, precision, left-justify)
// 1. Handles NULL strings by replacing with (null)
// 2. Calculates printable length based on precision
// 3. Sets padding spaces for alignment
// 4. Writes the string to the buffer with padding
//
// Note: Precision truncates the string; negative precision disables truncation
void	printf_str(t_data *data, char *s)
{
	int	print_len;
	int	is_null;

	is_null = 0;
	handle_null_str(data, &s, &is_null);
	print_len = get_print_len(data, s_len(s), is_null);
	set_str_padding(data, print_len);
	if (data->format.left_justified)
	{
		if (print_len > 0)
			putstr_buf_n(s, print_len, data);
		putchar_buf_n(' ', data->format.padding_spaces, data);
	}
	else
	{
		putchar_buf_n(' ', data->format.padding_spaces, data);
		if (print_len > 0)
			putstr_buf_n(s, print_len, data);
	}
}

// Handles NULL string edge cases
// 1. Replaces NULL with (null)
// 2. Adjusts precision for (null) truncation
//
// Note: Called by printf_str
static void	handle_null_str(t_data *data, char **s, int *is_null)
{
	if (*s != NULL)
		return ;
	*s = "(null)";
	*is_null = 1;
	if (data->format.precision_value >= 0 && data->format.precision_value < 5)
		data->format.precision_value = 0;
}

// Determines printable string lenght
// 1. Applies precision to truncate strings
// 2. Handles (null) edge cases
//
// Note: Precision -1 disables truncation
static int	get_print_len(t_data *data, int str_len, int is_null)
{
	int	precision;

	precision = data->format.precision_value;
	if (precision < 0)
		return (str_len);
	if (is_null && precision == 0)
		return (0);
	if (is_null && precision < 5)
		return (0);
	if (precision < str_len)
		return (precision);
	return (str_len);
}

// Calculates spaces-padding for strings
// 1. Computes padding based on width and printable length
//
// Note: Used for alignment in printf_str
static void	set_str_padding(t_data *data, int print_len)
{
	int	width;

	width = data->format.width_value;
	if (width <= 0)
		return ;
	data->format.padding_spaces = width - print_len;
	if (data->format.padding_spaces < 0)
		data->format.padding_spaces = 0;
}
