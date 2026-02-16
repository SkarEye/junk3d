/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 15:45:50 by mattcarniel       #+#    #+#             */
/*   Updated: 2026/02/16 17:14:30 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/mman.h>

#include "mapping.h"

bool	is_valid_name(const char *path)
{
	const char	*find;

	if (!path || strlen(path) < 5)
		return (false);
	find = memmem(path, strlen(path) + 1, ".cub\0", 5);
	if (!find || find[-1] == '/')
		return (false);
	return (true);
}

void	unmap_file(t_file *file)
{
	if (!file || !file->data || file->size <= 0)
		return ;
	munmap((void *)file->data, file->size);
	*file = (t_file){0};
}

t_file	file_open(const char *path)
{
	struct stat	st;
	t_file		file;
	int			fd;

	file.error = FERR_OK;
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return ((t_file){.error = FERR_OPEN});
	fstat(fd, &st);
	if (st.st_size <= 0)
		return ((t_file){.error = FERR_SIZE});
	file.data = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	if (file.data == MAP_FAILED)
		return ((t_file){.error = FERR_MMAP});
	close(fd);
	file.path = path;
	file.size = st.st_size;
	return (file);
}
