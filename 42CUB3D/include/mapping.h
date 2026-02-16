/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 16:51:42 by mattcarniel       #+#    #+#             */
/*   Updated: 2026/02/15 13:30:58 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAPPING_H
# define MAPPING_H

#include <stdbool.h>
#include <stddef.h>

typedef struct	s_file
{
	const char	*path;
	const char	*data;
	size_t		size;
}				t_file;

typedef struct s_params
{
	const char	*north_wall;
	const char	*south_wall;
	const char	*west_wall;
	const char	*east_wall;
	const char	*floor_color;
	const char	*ceiling_color;
}				t_params;

bool	is_valid_name(const char *path);

void	unmap_file(t_file *file);
t_file	map_file(const char *path);

#endif