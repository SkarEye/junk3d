/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 18:02:18 by mattcarniel       #+#    #+#             */
/*   Updated: 2026/02/09 18:17:07 by mattcarniel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMAGE_H
# define IMAGE_H

# ifndef WIN_H
#  define WIN_H 600
# endif

# ifndef WIN_W
#  define WIN_W 800
# endif

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		pxl_w;
	int		pxl_h;
	int		bits_per_pxl;
	int		line_length;
	int		endian;
}			t_data;

#endif
