/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caide-so <caide-so@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 19:55:54 by caide-so          #+#    #+#             */
/*   Updated: 2025/07/02 23:32:40 by caide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

static void	parse_flags(t_data *data);
static void	get_value(t_data *data, int *value);
static int	ft_atoi_printf(t_data *data);

// Parses format specifiers (flags, width, precision, specifier)
// 1. Resets t_format struct
// 2. Extracts flags
// 3. Parses width and precision
// 4. Validates and sets the conversion specifier
//
// Note: Returns -1 on invalid specifiers
int	parse_format(t_data *data)
{
	ft_memset(&data->format, 0, sizeof(t_format));
	data->format.precision_value = -1;
	parse_flags(data);
	get_value(data, &data->format.width_value);
	if (*data->s == '.' && *(data->s++))
		get_value(data, &data->format.precision_value);
	if (!in(SPECIFIERS, *data->s))
		return (-1);
	else
	{
		data->format.specifier = *data->s;
		if (in("diu", data->format.specifier))
			data->format.base = 10;
		else if (in("xXp", data->format.specifier))
		{
			data->format.base = 16;
			if (data->format.specifier == 'X')
				data->format.upper_case = 1;
		}
	}
	return (0);
}

// Extracts flags from the format string
// 1. Iterates over FLAGS characters
// 2. Updates t_format flags
//
// Note: Called during parse_format
static void	parse_flags(t_data *data)
{
	char	flag;

	while (in(FLAGS, *data->s))
	{
		flag = *data->s;
		if (flag == '+')
			data->format.plus = 1;
		else if (flag == '-')
			data->format.left_justified = 1;
		else if (flag == ' ')
			data->format.space = 1;
		else if (flag == '0')
			data->format.zero_pad = 1;
		else if (flag == '#')
			data->format.hash = 1;
		data->s++;
	}
}

// Parses width/precision values
// 1. Reads * to fetch value from va_list
// 2. Otherwise, parses numeric value from the format string
//
// Note: Used for both width and precision parsing
static void	get_value(t_data *data, int *value)
{
	if (*data->s == '*')
	{
		*value = va_arg(data->ap, int);
		data->s++;
		return ;
	}
	*value = ft_atoi_printf(data);
}

// Converts a numeric substring to an integer
// 1. Reads digits from the format string
// 2. Returns parsed integer value
//
// Note: Helper for get_value during width/precision parsing
static int	ft_atoi_printf(t_data *data)
{
	int	value;

	value = 0;
	while (in(NUMBERS, *data->s))
	{
		value = (value * 10) + (*data->s - '0');
		data->s++;
	}
	return (value);
}
