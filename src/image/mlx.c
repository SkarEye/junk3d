/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 18:02:10 by mattcarniel       #+#    #+#             */
/*   Updated: 2026/02/09 18:14:28 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <string.h>
#include <stdlib.h>

#include "image.h"

/**
 * @brief Clears all pixels of an image (set to black).
 *
 * @param img Image
 */
void	clear_image(t_data *img)
{
	if (img)
		memset(img->addr, 0, img->pxl_w * img->pxl_h * (img->bits_per_pxl / 8));
}

/**
 * @brief Destroys an image and frees its pointer.
 *
 * @param mlx MLX pointer
 * @param img Image
 */
void	free_image(void *mlx, t_data *data)
{
	if (!data)
		return ;
	if (mlx && data->img)
		mlx_destroy_image(mlx, data->img);
	free(data);
	data = NULL;
}

/**
 * @brief Makes a new image.
 *
 * @param mlx MLX pointer
 * @param width Width of image
 * @param height Height of image
 * @return A pointer to the new image.
 */
t_data	*make_blank_image(void *mlx, int width, int height)
{
	t_data	*data;

	if (!mlx)
		return (NULL);
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->img = mlx_new_image(mlx, width, height);
	if (!data->img)
		return (free(data), NULL);
	data->addr = mlx_get_data_addr(data->img,
			&data->bits_per_pxl, &data->line_length, &data->endian);
	if (!data->addr)
		return (free_image(mlx, data), NULL);
	data->pxl_w = width;
	data->pxl_h = height;
	clear_image(data);
	return (data);
}

/**
 * @brief Gets an image from a .xpm file.
 *
 * @param mlx MLX pointer
 * @param file Filename
 *@return A pointer to the new image.
 */
t_data	*get_image_from_xpm(void *mlx, char *file)
{
	t_data	*data;

	if (!mlx || !file)
		return (NULL);
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->img = mlx_xpm_file_to_image(mlx, file, &data->pxl_w, &data->pxl_h);
	if (!data->img)
		return (free(data), NULL);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pxl,
			&data->line_length, &data->endian);
	if (!data->addr)
		return (free_image(mlx, data), NULL);
	return (data);
}
