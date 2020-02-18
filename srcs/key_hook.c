/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcanteau <jcanteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 15:41:09 by jcanteau          #+#    #+#             */
/*   Updated: 2020/02/18 18:08:36 by jcanteau         ###   ########.fr       */
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
		if (wolf->event.type == SDL_KEYUP)
		{
			if (wolf->event.key.keysym.sym == SDLK_w)
				wolf->cam.forward = FALSE;
			else if (wolf->event.key.keysym.sym == SDLK_a)
				wolf->cam.strafe_left = FALSE;
			else if (wolf->event.key.keysym.sym == SDLK_s)
				wolf->cam.backward = FALSE;
			else if (wolf->event.key.keysym.sym == SDLK_d)
				wolf->cam.strafe_right = FALSE;
			else if (wolf->event.key.keysym.sym == SDLK_RIGHT)
				wolf->cam.rotate_right = FALSE;
			else if (wolf->event.key.keysym.sym == SDLK_LEFT)
				wolf->cam.rotate_left = FALSE;
		}
		else if (wolf->event.type == SDL_QUIT)
			ft_exit(wolf, EXIT_SUCCESS, NULL);

		//refresh new position
		if (wolf->cam.strafe_right == TRUE)
		{
			wolf->cam.pos_x -= cos(wolf->cam.angle) * MOVE_SPEED;
			wolf->cam.pos_y += sin(wolf->cam.angle) * MOVE_SPEED;
		}
		if (wolf->cam.strafe_left == TRUE)
		{
			wolf->cam.pos_x += cos(wolf->cam.angle) * MOVE_SPEED;
			wolf->cam.pos_y -= sin(wolf->cam.angle) * MOVE_SPEED;
		}
		if (wolf->cam.backward == TRUE)
		{
			wolf->cam.pos_x -= sin(wolf->cam.angle) * MOVE_SPEED;
			wolf->cam.pos_y -= cos(wolf->cam.angle) * MOVE_SPEED;
		}
		if (wolf->cam.forward == TRUE)
		{
			wolf->cam.pos_x += sin(wolf->cam.angle) * MOVE_SPEED;
			wolf->cam.pos_y += cos(wolf->cam.angle) * MOVE_SPEED;
		}
		if (wolf->cam.rotate_left == TRUE)
			wolf->cam.angle += ROTATE_SPEED;
		if (wolf->cam.rotate_right == TRUE)
			wolf->cam.angle -= ROTATE_SPEED;
		ft_print(wolf);
	}
}
