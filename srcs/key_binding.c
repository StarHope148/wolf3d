/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_binding.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcanteau <jcanteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 12:16:41 by jcanteau          #+#    #+#             */
/*   Updated: 2020/06/21 12:31:58 by jcanteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void        ft_settings(t_env *wolf)
{
    if (wolf->event.key.keysym.sym == SDLK_KP_PLUS)
	{
		if (wolf->precision - RAY_LENGHT_STEP > 0)
			wolf->precision -= RAY_LENGHT_STEP;
		printf("ray lenght = %f\n", wolf->precision);			//DEBUG
	}
	else if (wolf->event.key.keysym.sym == SDLK_KP_MINUS)
	{
		wolf->precision += RAY_LENGHT_STEP;
		printf("ray lenght = %f\n", wolf->precision);			//DEBUG

	}
	else if (wolf->event.key.keysym.sym == SDLK_x)
	{
		printf("---------------------\n");
		printf("cam_x = %.2f\tcam_y = %.2f\n", wolf->cam.pos_x, wolf->cam.pos_y);	//DEBUG			
		//printf("case = %c\n", wolf->mapdata.map[(int)wolf->cam.pos_y][(int)wolf->cam.pos_x]);
		printf("angle = %f\n", wolf->cam.angle);
	}
	else
		printf("keycode = %d\n", wolf->event.key.keysym.sym);		//DEBUG
}

void        ft_movement(t_env *wolf)
{
	if (wolf->event.key.keysym.sym == SDLK_w)
		wolf->cam.forward = TRUE;
	else if (wolf->event.key.keysym.sym == SDLK_a)
		wolf->cam.strafe_left = TRUE;
	else if (wolf->event.key.keysym.sym == SDLK_s)
		wolf->cam.backward = TRUE;
	else if (wolf->event.key.keysym.sym == SDLK_d)
		wolf->cam.strafe_right = TRUE;
	else if (wolf->event.key.keysym.sym == SDLK_RIGHT)
		wolf->cam.rotate_right = TRUE;
	else if (wolf->event.key.keysym.sym == SDLK_LEFT)
		wolf->cam.rotate_left = TRUE;
}