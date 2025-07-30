/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcudos <marcudos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 20:55:15 by marcudos          #+#    #+#             */
/*   Updated: 2025/07/26 01:07:37 by marcudos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_H
# define COLORS_H

// Reset
# define RESET        "\033[0m"

// Regular colors
# define BLACK        "\033[0;30m"
# define RED          "\033[0;31m"
# define GREEN        "\033[0;32m"
# define YELLOW       "\033[0;33m"
# define BLUE         "\033[0;34m"
# define MAGENTA      "\033[0;35m"
# define CYAN         "\033[0;36m"
# define WHITE        "\033[0;37m"

// Bold
# define BBLACK       "\033[1;30m"
# define BRED         "\033[1;31m"
# define BGREEN       "\033[1;32m"
# define BYELLOW      "\033[1;33m"
# define BBLUE        "\033[1;34m"
# define BMAGENTA     "\033[1;35m"
# define BCYAN        "\033[1;36m"
# define BWHITE       "\033[1;37m"

# define COLOR_FLOOR 0xCCCCCC
# define COLOR_FOV 0xFFFFFF
# define COLOR_WALL  0x444444
# define COLOR_VOID  0x000000
# define COLOR_GREEN 0x00FF00
# define COLOR_RED 0xFF0000
# define COLOR_BLUE 0x2B58DE // 0x577AE4

#endif
