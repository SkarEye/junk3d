/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 16:51:42 by mattcarniel       #+#    #+#             */
/*   Updated: 2026/02/16 17:15:24 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAPPING_H
# define MAPPING_H

# include <stddef.h>

typedef enum e_file_error {
	FERR_OK,
	FERR_OPEN,
	FERR_SIZE,
	FERR_MMAP,
}	t_file_error;

typedef struct s_file
{
	const char		*path;
	const char		*data;
	size_t			size;
	t_file_error	error;
}	t_file;

#endif
