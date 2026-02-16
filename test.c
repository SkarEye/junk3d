/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 17:15:54 by smamalig          #+#    #+#             */
/*   Updated: 2026/02/16 16:46:17 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>

typedef struct s_file {
	const char	*data;
	size_t		size;
}	t_file;

typedef struct s_vec2i {
	int	x;
	int	y;
}	t_vec2i;

typedef struct s_vec3i {
	int	x;
	int	y;
	int	z;
}	t_vec3i;

typedef struct s_map {
	const char	*view;
	int			*line_data;
	int			height;
}	t_map;

t_file	file_open(const char *path)
{
	struct stat	st;
	t_file		file;
	int			fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return ((t_file){0});
	fstat(fd, &st);
	if (st.st_size < 0)
		return ((t_file){0});
	file.data = mmap(0, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	if (file.data == MAP_FAILED)
		return ((t_file){0});
	file.size = st.st_size;
	close(fd);
	return (file);
}

int	count_lines(t_file file)
{
	size_t	i;
	int		n;

	n = 0;
	i = 0;
	while (i < file.size)
	{
		if (file.data[i] == '\n')
			n++;
		i++;
	}
	if (file.size > 0 && file.data[file.size - 1] != '\n')
		n++;
	return (n);
}

t_map	init_map(t_file file, int *line_data, int height)
{
	size_t	off;
	int		line;

	line_data[0] = 0;
	line = 1;
	off = 0;
	while (off < file.size)
	{
		if (file.data[off] == '\n' && line <= height)
			line_data[line++] = off + 1;
		off++;
	}
	line_data[height] = file.size;
	return ((t_map){file.data, line_data, height});
}

int	line_len(t_map *map, int y)
{
	int	len;

	len = map->line_data[y + 1] - map->line_data[y];
	if (len > 0 && map->view[map->line_data[y] + len - 1] == '\n')
		len--;
	return (len);
}

int	map_at(t_map *map, int x, int y)
{
	if (y < 0 || y >= map->height)
		return (-1);
	if (x < 0 || x >= line_len(map, y))
		return (-1);
	return ((unsigned char)map->view[map->line_data[y] + x]);
}

t_vec2i	get_player_position(t_file file)
{
	t_vec2i	save;
	t_vec2i	pos;
	size_t	off;
	size_t	count;

	off = 0;
	count = 0;
	pos = (t_vec2i){0, 0};
	while (off < file.size)
	{
		if (file.data[off] == 'N' || file.data[off] == 'S'
			|| file.data[off] == 'E' || file.data[off] == 'W')
		{
			save = pos;
			count++;
		}
		if (file.data[off] == '\n')
			pos = (t_vec2i){-1, pos.y + 1};
		pos.x++;
		off++;
	}
	if (count != 1)
		return ((t_vec2i){-count - 1, -count - 1});
	return (save);
}

static int	flood_step(t_map *map, uint8_t *vis, t_vec2i *stk, int *top)
{
	const int	d[] = {0, -1, 0, 1, -1, 0, 1, 0};
	t_vec2i		cur;
	t_vec2i		nb;
	int			i;
	int			c;

	cur = stk[--(*top)];
	i = 0;
	while (i < 8)
	{
		nb = (t_vec2i){cur.x + d[i], cur.y + d[i + 1]};
		c = map_at(map, nb.x, nb.y);
		if (c < 0 || c == ' ')
			return (-1);
		if (c != '1' && !vis[map->line_data[nb.y] + nb.x])
		{
			vis[map->line_data[nb.y] + nb.x] = 1;
			stk[(*top)++] = nb;
		}
		i += 2;
	}
	return (0);
}

int	flood(t_file file, t_vec2i start)
{
	int		height;
	t_map	map;
	uint8_t	*vis;
	t_vec2i	*stk;
	int		top;

	height = count_lines(file);
	map = init_map(file,
			__builtin_alloca((height + 1) * sizeof(int)), height);
	vis = __builtin_alloca(file.size);
	memset(vis, 0, file.size);
	stk = __builtin_alloca(file.size * sizeof(t_vec2i));
	top = 0;
	vis[map.line_data[start.y] + start.x] = 1;
	stk[top++] = start;
	while (top > 0)
	{
		if (flood_step(&map, vis, stk, &top) < 0)
			return (printf("map not enclosed\n"), -1);
	}
	return (printf("map OK\n"), 0);
}

int	main(void)
{
	t_file	file;
	t_vec2i	player;

	file = file_open("test.txt");
	if (!file.data)
		return (1);
	player = get_player_position(file);
	printf("player at (%i, %i)\n", player.x, player.y);
	if (player.x < 0)
		return (1);
	return (flood(file, player) < 0);
}
