/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcanteau <jcanteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 11:55:03 by jcanteau          #+#    #+#             */
/*   Updated: 2020/06/22 13:49:56 by jcanteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_init_env(t_env *wolf)
{
	wolf->window = NULL;
	wolf->renderer = NULL;
	wolf->texture = NULL;
	wolf->format = NULL;
	wolf->screen_pixels = NULL;
	wolf->mapdata.nbcol = 0;
	wolf->mapdata.nbl = 0;
	wolf->mapdata.cur_line = 0;
	wolf->mapdata.map = NULL;

	wolf->cam.pos_x = 1.5;
	wolf->cam.pos_y = 7.5;
	wolf->cam.angle = PI/2;
	wolf->cam.fov = FOV;
	wolf->cam.strafe_left = 0;
	wolf->cam.strafe_right = 0;
	wolf->cam.forward = 0;
	wolf->cam.backward = 0;
	wolf->cam.rotate_left = 0;
	wolf->cam.rotate_right = 0;

	wolf->precision = RAY_LENGHT;
}

void		ft_initialize(t_env *wolf, char *mapfile)
{
    ft_init_env(wolf);
	ft_init_map(wolf, mapfile);
}
