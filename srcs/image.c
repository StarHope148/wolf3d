/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcanteau <jcanteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 16:04:06 by jcanteau          #+#    #+#             */
/*   Updated: 2020/01/22 18:31:26 by jcanteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_print(t_env *wolf)
{
	//###### printing 2D map view from above + red dot for camera location ######
	int	i;
	int	j;

	void	*tmp;
	int		pitch;
	SDL_bool done;

	int		x;
	int		y;
	int		def_x;
	int		def_y;
	
	SDL_LockTexture(wolf->texture, NULL, &tmp, &pitch);
	wolf->pixels = tmp;
	i = 0;
	while (i < (int)wolf->mapdata.nbl)
	{
		j = 0;
		while (j < (int)wolf->mapdata.nbcol)
		{
			done = 0;
			x = j * BLOCK;
			y = i * BLOCK;
			def_x = x;
			def_y = y;
			if (wolf->mapdata.map[i][j] == WALL)
				while (done == 0)
				{
					wolf->pixels[y * WIDTH + x] = LIME;
					//pixels[(y + BLOCK)* WIDTH + x + BLOCK] = 0xFF000000;  //<--- opposite corner position of block
					x++;
					if (x > def_x + BLOCK)
					{
						x = j * BLOCK;
						y++;
					}
					if (y > def_y + BLOCK)
						done = 1;
				}
			else if (wolf->mapdata.map[i][j] == EMPTY)
				while (done == 0)
				{
					wolf->pixels[y * WIDTH + x] = GRAY;
					x++;
					if (x > def_x + BLOCK)
					{
						x = j * BLOCK;
						y++;
					}
					if (y > def_y + BLOCK)
						done = 1;
				}
			j++;
		}
		i++;
	}
	//---------------------------------------------------------------------------------------------------------

	// ###### RAYTRACER ###### 
	int		screen_column_x = 0;
	int		hit = 0;
	int		side = 0;
	double	perpWallDist = 0;
	double	hauteurLigne = 0;
	int		drawStart = 0;
	int		drawEnd = 0;

	while (screen_column_x < WIDTH)
	{
		wolf->ray.camera_x = (2 * screen_column_x / WIDTH) - 1;
		wolf->ray.pos_x = wolf->cam.pos_x;
		wolf->ray.pos_y = wolf->cam.pos_y;
		wolf->ray.dir_x = wolf->cam.dir_x + wolf->cam.plane_x * wolf->ray.camera_x;
		wolf->ray.dir_y = wolf->cam.dir_y + wolf->cam.plane_y * wolf->ray.camera_x;
		wolf->ray.map_x = (int)wolf->ray.pos_x;
		wolf->ray.map_y = (int)wolf->ray.pos_y;
		wolf->ray.delta_x = sqrt(1 + (wolf->ray.dir_y * wolf->ray.dir_y) / (wolf->ray.dir_x * wolf->ray.dir_x));
		wolf->ray.delta_y = sqrt(1 + (wolf->ray.dir_x * wolf->ray.dir_x) / (wolf->ray.dir_y * wolf->ray.dir_y));
		if (wolf->ray.dir_x < 0)
		{
			wolf->ray.step_x = -1;
			wolf->ray.length_x = (wolf->ray.pos_x - wolf->ray.map_x) * wolf->ray.delta_x;
		}
		else
		{
			wolf->ray.step_x = 1;
			wolf->ray.length_x = (wolf->ray.map_x + 1 - wolf->ray.pos_x) * wolf->ray.delta_x;

		}
		if (wolf->ray.dir_y < 0)
		{
			wolf->ray.step_y = -1;
			wolf->ray.length_y = (wolf->ray.pos_y - wolf->ray.map_y) * wolf->ray.delta_y;
		}
		else
		{
			wolf->ray.step_y = 1;
			wolf->ray.length_y = (wolf->ray.map_y + 1 - wolf->ray.pos_y) * wolf->ray.delta_y;
		}
		while (hit == 0)
		{
			if (wolf->ray.length_x < wolf->ray.length_y)
			{
				wolf->ray.length_x += wolf->ray.delta_x;
				wolf->ray.map_x += wolf->ray.step_x;
				side = 0;
			}
			else
			{
				wolf->ray.length_y += wolf->ray.delta_y;
				wolf->ray.map_y += wolf->ray.step_y;
				side = 1;
			}

			//few check to avoid segfault
			if (wolf->ray.map_x >= wolf->mapdata.nbcol)
				wolf->ray.map_x = wolf->mapdata.nbcol - 1;
			else if (wolf->ray.map_x < 0)
				wolf->ray.map_x = 0;
			if (wolf->ray.map_y >= wolf->mapdata.nbl)
				wolf->ray.map_y = wolf->mapdata.nbl - 1;
			else if (wolf->ray.map_y < 0)
				wolf->ray.map_y = 0;

			if (wolf->mapdata.map[wolf->ray.map_y][wolf->ray.map_x] == WALL)
				hit = 1; //to break the loop
		}

		// Optical correction (fixing fish-eye effect)
		if (side == 0)
			perpWallDist = fabs((wolf->ray.map_x - wolf->ray.pos_x + (1 - wolf->ray.step_x) / 2) / wolf->ray.dir_x);
		else
			perpWallDist = fabs((wolf->ray.map_y - wolf->ray.pos_y + (1 - wolf->ray.step_y) / 2) / wolf->ray.dir_y);

		// Calculate height of column to draw on screen
		hauteurLigne = fabs((double)HEIGHT / perpWallDist);
		drawStart = (int)(-hauteurLigne / 2 + HEIGHT / 2);
		drawEnd = (int)(hauteurLigne / 2 + HEIGHT / 2);
		if (drawStart < BLOCK * wolf->mapdata.nbl)
			drawStart = BLOCK* wolf->mapdata.nbl;
		if (drawEnd > HEIGHT)
			drawEnd = HEIGHT - 1;

		// Filling pixels
		int		cur_height = drawStart;
		while (cur_height < drawEnd)
		{
			if (side == 1)
				wolf->pixels[cur_height * WIDTH + screen_column_x] = WHITE;
			else
				wolf->pixels[cur_height * WIDTH + screen_column_x] = SILVER;
			cur_height++;
		}
		
		screen_column_x++;
	}
	//---------------------------------------------------------------------------------------------------------

	// ###### DISPLAYING ######
	SDL_UnlockTexture(wolf->texture);
	SDL_RenderCopy(wolf->renderer, wolf->texture, NULL, NULL);

	//SDL_RenderDrawPoint(wolf->renderer, wolf->cam.pos_x, wolf->cam.pos_y);
	SDL_SetRenderDrawColor(wolf->renderer, 255, 0, 0, 255);
	
	SDL_RenderDrawLine(wolf->renderer, wolf->cam.pos_x * BLOCK, wolf->cam.pos_y * BLOCK, BLOCK, BLOCK); //RAY from cam

	SDL_RenderPresent(wolf->renderer);
}