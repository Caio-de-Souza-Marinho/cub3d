/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caide-so <caide-so@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 03:35:09 by caide-so          #+#    #+#             */
/*   Updated: 2024/12/26 03:35:16 by caide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

# define BUF_SIZE 4096
# define FLAGS "+- 0#"
# define NUMBERS "0123456789"
# define SPECIFIERS "cspdiuxX%"
# define LOW_HEX "0123456789abcdef"
# define UP_HEX "0123456789ABCDEF"

// Union to handle integer values for both signed and unsigned types
//
// Members:
// uint64: Stores unsigned 64-bit integer values (e.g., pointers, hex values)
//
// int64: Stores signed 64-bit integer values (e.g., decimal integers)
//
// Note: Used to simplify conversions for different specifiers(e.g., %d, %p, %x)
typedef union t_union_int
{
	unsigned long	uint64;
	long			int64;
}	t_union_int;

// Stores formatting options parsed from the format string
//
// Members:
// plus: + flag
//
// left_justified: - flag
//
// space: ' ' flag
//
// zero_pad: 0 flag
//
// hash: # flag
//
// specifier: Conversion specifier (c, s, d, x)
//
// width_value: width field value
//
// precision_value: precision field value
//
// buf_temp: Temporary buffer for number-to-string conversions
//
// nbr_len: Length of the converted number string
//
// upper_case: Flag for uppercase hex (X)
//
// base: Numeric base (10 for decimal, 16 for hex)
//
// padding_spaces: Calculated space padding value
//
// padding_zeros: Calculated zeros padding value
//
// signed_value: Boolean for signed or unsigned number
//
// is_negative: Boolean for negative or positive number
//
// is_converted: Boolean for state converted or not
//
// Note: Reset for each new format specifier during parsing
typedef struct s_format
{
	int		plus;
	int		left_justified;
	int		space;
	int		zero_pad;
	int		hash;
	char	specifier;
	int		width_value;
	int		precision_value;
	char	buf_temp[64];
	int		nbr_len;
	int		upper_case;
	int		base;
	int		padding_spaces;
	int		padding_zeros;
	int		signed_value;
	int		is_negative;
	int		is_converted;
}	t_format;

// Main struct for managing the printf operation state
//
// Members:
// s: Pointer to the format string
//
// ap: va_list for variadic arguments
//
// chars_written: Total characters printed
//
// buf: Output buffer (4096 bytes)
//
// buffer_index: Current position in the buffer
//
// format: Struct holding parsed format options
typedef struct s_data
{
	const char	*s;
	va_list		ap;
	int			chars_written;
	char		*buf;
	int			buffer_index;
	t_format	format;
}	t_data;

// PROTOTYPES

int		ft_printf(const char *format, ...);

// utils
void	*ft_memset(void *s, int c, size_t n);
int		in(const char *s, char c);
int		s_len(const char *s);

// parser
int		parse_format(t_data *data);

// buffer
void	write_buf(t_data *data, char c);
void	flush_buf(t_data *data);
void	putchar_buf_n(char c, int n, t_data *data);
void	putstr_buf_n(char *s, int precision, t_data *data);
void	itoa_buf(t_data *data, t_union_int int_values);

// print
void	printf_char(t_data *data, int c);
void	printf_str(t_data *data, char *s);
void	printf_int(t_data *data, t_union_int int_values);
void	put_sign(t_data *data);
int		handle_nil_pointer(t_data *data);
void	print_nil_ptr(t_data *data, int width);
void	print_formatted_number(t_data *data);

#endif 
