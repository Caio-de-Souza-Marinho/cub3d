/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_int.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caide-so <caide-so@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 21:49:10 by caide-so          #+#    #+#             */
/*   Updated: 2025/07/02 23:32:46 by caide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

static void	set_padding_zeros(t_data *data, t_union_int int_values);
static void	set_padding_zeros_pt_2(t_data *data);
static void	set_padding_spaces(t_data *data);

// Handles integer conversions (%d, %u, %x, %X, %p)
// 1. Converts the number to a string via itoa_buf
// 2. Calculates padding (zeros and spaces)
// 3. Prints the formatted number with signs/prefixes
//
// Note: Uses t_union_int to handle signed/unsigned values
void	printf_int(t_data *data, t_union_int int_values)
{
	if (data->format.specifier == 'p' && int_values.uint64 == 0)
	{
		if (handle_nil_pointer(data))
			return ;
	}
	itoa_buf(data, int_values);
	set_padding_zeros(data, int_values);
	set_padding_spaces(data);
	print_formatted_number(data);
}

// Calculates zero-padding for numbers
// 1. Handles precision-based zero padding
// 2. Adjusts for edge cases (e.g., %p widh 0 flag)
//
// Note: Called by print_int
static void	set_padding_zeros(t_data *data, t_union_int int_values)
{
	if (data->format.precision_value == 0 && int_values.uint64 == 0
		&& data->format.specifier != 'p')
	{
		data->format.nbr_len = 0;
		data->format.buf_temp[0] = '\0';
		if (data->format.hash && in("xX", data->format.specifier))
			data->format.hash = 0;
	}
	if (data->format.precision_value >= 0)
	{
		if (data->format.precision_value > data->format.nbr_len)
		{
			data->format.padding_zeros = data->format.precision_value
				- data->format.nbr_len;
			return ;
		}
	}
	set_padding_zeros_pt_2(data);
}

// Secondary zero-padding logic for edge cases
// 1. Adjusts padding for hex/pointer prefixex (0x)
// 2. Accounts for sign/space flags
//
// Note: Split from set_padding_zeros for readability
static void	set_padding_zeros_pt_2(t_data *data)
{
	if (data->format.specifier == 'p')
	{
		if (data->format.zero_pad && data->format.precision_value < 0)
			data->format.padding_zeros = data->format.width_value
				- data->format.nbr_len - 2;
		else
			data->format.padding_zeros = 0;
		return ;
	}
	if (data->format.zero_pad && !data->format.left_justified
		&& data->format.precision_value < 0)
		data->format.padding_zeros = data->format.width_value
			- data->format.nbr_len;
	if (data->format.specifier == 'u')
		return ;
	else if ((in("xX", data->format.specifier) && data->format.hash
			&& data->format.buf_temp[0] != '0'))
		data->format.padding_zeros -= 2;
	else if (data->format.is_negative || (!data->format.is_negative
			&& (data->format.plus || data->format.space)))
		data->format.padding_zeros--;
	if (data->format.padding_zeros < 0)
		data->format.padding_zeros = 0;
	return ;
}

// Calculates space-padding for alignment
// 1. Accounts for sign/prefix characters
// 2. Computes total padding spaces
//
// Note: Used for left/right alignment in printf_int
static void	set_padding_spaces(t_data *data)
{
	int	total_len;
	int	prefix_len;

	total_len = data->format.nbr_len + data->format.padding_zeros;
	prefix_len = 0;
	if (data->format.is_negative || (!data->format.is_negative
			&& (data->format.plus || data->format.space)))
		prefix_len = 1;
	if (data->format.hash && data->format.base == 16
		&& data->format.buf_temp[0] != '0' && data->format.specifier != 'p')
		prefix_len = 2;
	if (data->format.specifier == 'p' && data->format.buf_temp[0] != '\0')
		prefix_len = 2;
	data->format.padding_spaces = data->format.width_value - total_len
		- prefix_len;
	if (data->format.padding_spaces < 0)
		data->format.padding_spaces = 0;
}

// Prints sign/prefix for numerics (e.g., -, +, 0x)
// 1. Adds - for negatives, +/' ' for positives (if flags set)
// 2. Adds 0x/ 0X for hex/pointer values
//
// Note: Called during integer/pointer formatting
void	put_sign(t_data *data)
{
	if (data->format.base == 16)
	{
		if ((in("xX", data->format.specifier) && data->format.hash
				&& data->format.buf_temp[0] != '0')
			|| data->format.specifier == 'p')
		{
			if (data->format.upper_case)
				putstr_buf_n("0X", 2, data);
			else
				putstr_buf_n("0x", 2, data);
		}
	}
	else if (data->format.signed_value)
	{
		if (data->format.is_negative)
			putchar_buf_n('-', 1, data);
		else if (!data->format.is_negative)
		{
			if (data->format.plus)
				putchar_buf_n('+', 1, data);
			else if (!data->format.plus && data->format.space)
				putchar_buf_n(' ', 1, data);
		}
	}
}
