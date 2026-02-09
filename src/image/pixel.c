/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 15:01:42 by mattcarniel       #+#    #+#             */
/*   Updated: 2026/02/09 18:17:05 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

#include "image.h"

/**
 * @brief Sets a given color value to a pixel.
 *
 * @param x horizontal coordinates
 * @param y vertical coordinates
 * @param c Color
 * @param data Image pointer
 */
void	set_pixel( uint32_t x, uint32_t y, uint32_t color, t_data *data)
{
	char	*dst;

	if (!data || x >= data->pxl_w || y >= data->pxl_h)
		return ;
	if (color > 0xFFFFFF)
		color = 0xFFFFFF;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pxl / 8));
	*(unsigned int *)dst = color;
}

/**
 * @brief Adds a given color value to a pixel.
 *
 * @param x horizontal coordinates
 * @param y vertical coordinates
 * @param c Color
 * @param data Image pointer
 */
void	add_pixel(uint32_t x, uint32_t y, unsigned int color, t_data *data)
{
	char	*dst;

	if (!data || x >= data->pxl_w || y >= data->pxl_h || y < 0)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pxl / 8));
	color += *(unsigned int *)dst;
	if (color > 0xFFFFFF)
		color = 0xFFFFFF;
	*(unsigned int *)dst = color;
}

/**
 * @brief Gives the given color value of a pixel.
 *
 * @param x horizontal coordinates
 * @param y vertical coordinates
 * @param data Image pointer
 * @return Color value of the pixel.
 */
unsigned int	get_pixel(uint32_t x, uint32_t y, t_data *data)
{
	char	*src;

	if (!data || x >= data->pxl_w || x < 0 || y >= data->pxl_h || y < 0)
		return (0);
	src = data->addr + y * data->line_length + x * (data->bits_per_pxl / 8);
	return (*(unsigned int *)src);
}

/** 
 * @brief Scales a pixel by a given factor and sets the color value to the scaled area.
 */
void	scale_pixel(uint32_t x, uint32_t y, uint32_t color, int scale, t_data *dst)
{
	uint32_t	i;
	uint32_t	j;

	if (!dst)
		return ;
	j = 0;
	while (j < y + scale)
	{
		i = x;
		while (i < x + scale)
		{
			set_pixel(i, j, color, dst);
			i++;
		}
		j++;
	}
}

unsigned int	blend_colors(uint32_t src, uint32_t dst, float t)
{
	int	r;
	int	g;
	int	b;

	if (t < 0)
		return (src);
	if (t > 1)
		return (dst);
	r = ((1 - t) * ((src >> 16) & 0xFF)) + (t * ((dst >> 16) & 0xFF));
	g = ((1 - t) * ((src >> 8) & 0xFF)) + (t * ((dst >> 8) & 0xFF));
	b = ((1 - t) * (src & 0xFF)) + (t * (dst & 0xFF));
	return (r << 16 | g << 8 | b);
}
