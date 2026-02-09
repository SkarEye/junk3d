/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 16:51:42 by mattcarniel       #+#    #+#             */
/*   Updated: 2026/02/09 16:52:14 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAPPING_H
# define MAPPING_H

#include <stddef.h>

typedef struct	s_file
{
	const char	*path;
	const char	*data;
	size_t		size;
}				t_file;

#endif