/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcanteau <jcanteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 15:41:09 by jcanteau          #+#    #+#             */
/*   Updated: 2020/01/28 17:46:05 by jcanteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"


void	ft_key_hook(t_env *wolf)
{
	while (1)
	{
    	SDL_PollEvent(&wolf->event);
		if (wolf->event.type == SDL_KEYDOWN)
		{
			if (wolf->event.key.keysym.sym == SDLK_ESCAPE)
				ft_exit(wolf, EXIT_SUCCESS, NULL);
			else if (wolf->event.key.keysym.sym == SDLK_w)
				wolf->cam.forward_backward = -1;
			else if (wolf->event.key.keysym.sym == SDLK_a)
				wolf->cam.vel_x = -1;
			else if (wolf->event.key.keysym.sym == SDLK_s)
				wolf->cam.forward_backward = 1;
			else if (wolf->event.key.keysym.sym == SDLK_d)
				wolf->cam.vel_x = 1;
			else if (wolf->event.key.keysym.sym == SDLK_RIGHT)
				wolf->cam.angle += ROTATE_SPEED;
			else if (wolf->event.key.keysym.sym == SDLK_LEFT)
				wolf->cam.angle -= ROTATE_SPEED;
			else if (wolf->event.key.keysym.sym == SDLK_x)
			{
				printf("---------------------\n");
				printf("cam_x = %.2f\tcam_y = %.2f\ncase[%d][%d]\tmap_x = %d map_y = %d\n", wolf->cam.pos_x, wolf->cam.pos_y, wolf->ray.map_x, wolf->ray.map_y, wolf->ray.map_x, wolf->ray.map_y);	//DEBUG			
				printf("case = %c\n", wolf->mapdata.map[(int)wolf->cam.pos_y][(int)wolf->cam.pos_x]);
				printf("angle = %f\n", wolf->cam.angle);
			}
			else
				printf("keycode = %d\n", wolf->event.key.keysym.sym);		//DEBUG
		}
		else if (wolf->event.type == SDL_KEYUP)
		{
			if (wolf->event.key.keysym.sym == SDLK_w)
				wolf->cam.forward_backward = 0;
			else if (wolf->event.key.keysym.sym == SDLK_a)
				wolf->cam.vel_x = 0;
			else if (wolf->event.key.keysym.sym == SDLK_s)
				wolf->cam.forward_backward = 0;
			else if (wolf->event.key.keysym.sym == SDLK_d)
				wolf->cam.vel_x = 0;
		}
		else if (wolf->event.type == SDL_QUIT)
			ft_exit(wolf, EXIT_SUCCESS, NULL);

		if (wolf->cam.vel_x == 1)
		{
			wolf->cam.pos_x -= sin(wolf->cam.angle) * MOVE_SPEED;
			wolf->cam.pos_y -= cos(wolf->cam.angle) * MOVE_SPEED;
		}
		if (wolf->cam.vel_x == -1)
		{
			wolf->cam.pos_x += sin(wolf->cam.angle) * MOVE_SPEED;
			wolf->cam.pos_y += cos(wolf->cam.angle) * MOVE_SPEED;
		}
		if (wolf->cam.forward_backward == 1)
		{
			wolf->cam.pos_x -= sin(wolf->cam.angle) * MOVE_SPEED;
			wolf->cam.pos_y -= cos(wolf->cam.angle) * MOVE_SPEED;
		}
		if (wolf->cam.forward_backward == -1)
		{
			wolf->cam.pos_x += sin(wolf->cam.angle) * MOVE_SPEED;
			wolf->cam.pos_y += cos(wolf->cam.angle) * MOVE_SPEED;
		}
		ft_print(wolf);
	}
}
