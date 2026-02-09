/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 16:51:24 by mattcarniel       #+#    #+#             */
/*   Updated: 2026/02/09 18:16:59 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <string.h>

#include "mapping.h"

typedef struct s_params
{
	const char	*north_wall;
	const char	*south_wall;
	const char	*west_wall;
	const char	*east_wall;
	const char	*floor_color;
	const char	*ceiling_color;
}				t_params;

static char	*get_address(const char *data, size_t size, const char *key)
{
	char	*ret;

	ret = memmem(data, size, key, strlen(key) + 1);
	if (!ret)
		return (NULL);
	if (ret == data && ret[-1] != '\n')
		return (NULL);
	return (ret + strlen(key));
}

t_params	validate_params(t_file *file)
{
	t_params	p;

	if (!file || !file->data || file->size <= 0)
		return ((t_params){0}); //error
	p.north_wall = get_address(file->data, file->size, "NO ");
	p.south_wall = get_address(file->data, file->size, "SO ");
	p.west_wall = get_address(file->data, file->size, "WE ");
	p.east_wall = get_address(file->data, file->size, "EA ");
	p.floor_color = get_address(file->data, file->size, "F ");
	p.ceiling_color = get_address(file->data, file->size, "C ");
	if (!p.north_wall || !p.south_wall || !p.west_wall || !p.east_wall
		|| !p.floor_color || !p.ceiling_color)
		return ((t_params){0}); //error
	
	return (p);
}

