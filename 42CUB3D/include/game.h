#ifndef GAME_H
#define GAME_H

#include "cub3d.h"

#include "mapping.h"


typedef struct s_game
{
	void		*mlx;
	void		*win;
	void		*img;

	t_file		file;
	t_params	params;
}	t_game;

void init_game(t_game *game, t_data *data);

#endif