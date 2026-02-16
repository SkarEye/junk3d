/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 17:10:35 by mattcarniel       #+#    #+#             */
/*   Updated: 2026/02/16 17:40:53 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../game.h"
#include "mapping.h"

#include "../utils/error.h"

int	validate_map(t_game *game, const char *filename)
{
	t_params	p;

	if (!game)
		return (1); //print error ?
	if (!is_valid_name(filename))
		return (print_error(loc(F, L), ERR_INVALID_NAME, 1));
	game->file = map_file(filename);
	if (game->file.error)
		return (game->file.error);
	game->params = get_params(&game->file);
	if (game->params.error)
		return (game->params.error);
	// check if is playable, players ?
	{}
	return (0);
}