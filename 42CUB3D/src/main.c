/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 18:37:02 by fadzejli          #+#    #+#             */
/*   Updated: 2026/02/16 15:29:30 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

#include "../include/mapping.h"
#include "../include/error.h"
#include <cerrno>

static int	initialize_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx) //necessary check ?
		return (print_error(loc(F, L), ERR_MLX_INIT, 1));
	game->win = mlx_new_window(game->mlx, 1024, 1024, "Cub3D");
	if (!game->win)
		return (print_error(loc(F, L), ERR_MLX_WINDOW, 1));
	// can do better here
	// game->img = mlx_new_image(game->mlx, get_width(data.map), get_height(data.map));
	// if (!game->img)
		// return (print_error(loc(F, L), ERR_MLX_IMAGE, 1));
	return (0);
}

static void	hooks_and_loops(t_game *game)
{
	
}

int	main(int argc, char **argv)
{
	t_game	game;
	int		status;

	status = 0;

	//parsing
	{
	if (argc < 2 )
		return (print_error(loc(F, L), ERR_NO_ARGS, 1));
	else if (argc > 2)
		return (print_error(loc(F, L), ERR_MANY_ARGS, 1));
	if (!is_valid_name(argv[1]))
		return (print_error(loc(F, L), ERR_INVALID_NAME, 1));
	game.file = map_file(argv[1]);
	if (!game.file) // how to this check ?
		return (print_error(loc(F, L), ERR_PERROR, errno));
	status = parse_file(&game);
	if (status)
		return (free_game(&game), status);
	}
	//initialize game
	{
	initialize_game(&game);
	}
	//mlx
	{
	status = initialize_mlx(&game);
	if (status)
		return (free_game(&game), status);
	mlx_loop(game.mlx);
	}
	free_game(&game);
	return (0);
}
