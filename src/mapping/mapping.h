/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 16:51:42 by mattcarniel       #+#    #+#             */
/*   Updated: 2026/02/16 18:48:08 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAPPING_H
# define MAPPING_H

# include <stddef.h>

# include "../image/image.h"
# include "../utils/error.h"
typedef struct s_file
{
	const char		*path;
	const char		*data;
	size_t			size;
	t_error			error;
}	t_file;

typedef struct	s_params
{
	t_image		textures[4];
	uint32_t	floor_color;
	uint32_t	ceiling_color;
	t_error		error;
}	t_params;

bool		is_valid_name(const char *path);
void		unmap_file(t_file *file);
t_file		map_file(const char *path);

t_params	get_params(t_file *file);

#endif
