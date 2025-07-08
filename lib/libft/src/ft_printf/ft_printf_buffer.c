/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_buffer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caide-so <caide-so@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 14:15:29 by caide-so          #+#    #+#             */
/*   Updated: 2025/07/02 23:32:58 by caide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

// Writes the buffer to STDOUT and resets it
// 1. Calls write to output the buffer
// 2. Resets buffer_index and clears the buffer
//
// Note: Triggered when the buffer is full of parsing completes
void	flush_buf(t_data *data)
{
	data->chars_written += write(1, data->buf, data->buffer_index);
	ft_memset(data->buf, 0, BUF_SIZE);
	data->buffer_index = 0;
}

// Writes a single character to the buffer
// 1. Adds c to the buffer
// 2. Flushes the buffer if it reaches BUF_SIZE (4096)
//
// Note: Core buffer management function used by all output routines
void	write_buf(t_data *data, char c)
{
	if (data->buffer_index == BUF_SIZE)
		flush_buf(data);
	data->buf[data->buffer_index++] = c;
}

// Writes n copies of a character to the buffer
// 1. Repeats c for precision iterations
// 2. Skips if precision is <= 0
//
// Note: Used for padding (spaces/zeros) in formatted output
void	putchar_buf_n(char c, int precision, t_data *data)
{
	if (precision <= 0)
		return ;
	while (precision)
	{
		write_buf(data, c);
		precision--;
	}
}

// Writes a string to the buffer with precision-based truncation
// 1. Writes up to precision characters from s
// 2. Stops at string null terminator
//
// Note: Handles precision truncation for %s and hex/pointer prefixes
void	putstr_buf_n(char *s, int precision, t_data *data)
{
	if (precision <= 0)
		return ;
	while (precision && *s != '\0')
	{
		write_buf(data, *s);
		precision--;
		s++;
	}
}

// Recursively converts numbers to ASCII strings
// 1. Handles negative numbers
// 2. Builds string in reverse order into buf_temp
// 3. Supports base 10/16 (lower/uppercase hex)
//
// Note: Uses t_union_int for value storage
void	itoa_buf(t_data *data, t_union_int int_values)
{
	t_union_int	tmp_int_values;

	if (data->format.is_negative && !data->format.is_converted)
	{
		int_values.int64 = -(int_values.int64);
		data->format.is_converted = 1;
		itoa_buf(data, int_values);
	}
	else if (int_values.uint64 < (unsigned long)data->format.base)
	{
		if (data->format.upper_case)
			data->format.buf_temp[data->format.nbr_len++]
				= UP_HEX[int_values.uint64];
		else
			data->format.buf_temp[data->format.nbr_len++]
				= LOW_HEX[int_values.uint64];
	}
	else
	{
		tmp_int_values.uint64 = int_values.uint64 / data->format.base;
		itoa_buf(data, tmp_int_values);
		tmp_int_values.uint64 = int_values.uint64 % data->format.base;
		itoa_buf(data, tmp_int_values);
	}
}
