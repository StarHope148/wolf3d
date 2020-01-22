/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcanteau <jcanteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 15:41:09 by jcanteau          #+#    #+#             */
/*   Updated: 2020/01/22 12:51:25 by jcanteau         ###   ########.fr       */
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
				wolf->cam.vely = -1;
			else if (wolf->event.key.keysym.sym == SDLK_a)
				wolf->cam.velx = -1;
			else if (wolf->event.key.keysym.sym == SDLK_s)
				wolf->cam.vely = 1;
			else if (wolf->event.key.keysym.sym == SDLK_d)
				wolf->cam.velx = 1;
			else if (wolf->event.key.keysym.sym == SDLK_x)
				printf("cam.x = %.2f\tcam.y = %.2f\n", wolf->cam.x, wolf->cam.y);	//DEBUG			
			else
				printf("keycode = %d\n", wolf->event.key.keysym.sym);		//DEBUG
		}
		else if (wolf->event.type == SDL_KEYUP)
		{
			if (wolf->event.key.keysym.sym == SDLK_w)
				wolf->cam.vely = 0;
			else if (wolf->event.key.keysym.sym == SDLK_a)
				wolf->cam.velx = 0;
			else if (wolf->event.key.keysym.sym == SDLK_s)
				wolf->cam.vely = 0;
			else if (wolf->event.key.keysym.sym == SDLK_d)
				wolf->cam.velx = 0;
		}
		else if (wolf->event.type == SDL_QUIT)
			ft_exit(wolf, EXIT_SUCCESS, NULL);
	
		//wolf->pixels[(int)wolf->cam.y * WIDTH + (int)wolf->cam.x] == GRAY

		if (wolf->cam.velx == 1)
			wolf->cam.x += MOVE_SPEED;
		if (wolf->cam.velx == -1)
			wolf->cam.x -= MOVE_SPEED;
		if (wolf->cam.vely == 1)
			wolf->cam.y += MOVE_SPEED;
		if (wolf->cam.vely == -1)
			wolf->cam.y -= MOVE_SPEED;
		ft_print(wolf);
	}
}
