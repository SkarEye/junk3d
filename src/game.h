/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 17:04:59 by mattcarniel       #+#    #+#             */
/*   Updated: 2026/02/16 17:35:48 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# include <stdint.h>

# include "mapping/mapping.h"
# include "image/image.h"

typedef enum e_texture
{
	T_NW = 0,
	T_SW,
	T_WW,
	T_EW,
	T_UNKNOWN
}	t_texture;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	void		*img;

	t_file		file;
	t_params	params;
}	t_game;

#endif