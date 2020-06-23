/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcanteau <jcanteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 16:04:06 by jcanteau          #+#    #+#             */
/*   Updated: 2020/06/23 19:31:42 by jcanteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_print(t_env *wolf)
{
	
	SDL_LockTexture(wolf->texture, NULL, (void *)&(wolf->screen_pixels), &(wolf->pitch));
	wolf->pixels_wall_north = wolf->surface_wall_north->pixels;
	wolf->pixels_wall_south = wolf->surface_wall_south->pixels;
	wolf->pixels_wall_west = wolf->surface_wall_west->pixels;
	wolf->pixels_wall_east = wolf->surface_wall_east->pixels;

	//---------------------------------------------------------------------------------------------------------

	// ###### RAYTRACER ###### 

	wolf->raycast.x_render = 0;
	while (wolf->raycast.x_render < WIDTH)
	{
		wolf->raycast.ray_angle = (wolf->cam.angle + wolf->cam.fov / 2.0) - ((double)wolf->raycast.x_render / (double)WIDTH) * wolf->cam.fov;
		wolf->raycast.distance_towall = 0;
		wolf->raycast.hit_wall = 0;
		wolf->raycast.shading = 1;

		wolf->raycast.eye_x = sin(wolf->raycast.ray_angle);
		wolf->raycast.eye_y = cos(wolf->raycast.ray_angle);

		while (wolf->raycast.hit_wall == 0 && wolf->raycast.distance_towall < MAX_DEPTH)
		{
			wolf->raycast.distance_towall += wolf->precision;
			wolf->raycast.shading -= RAY_LENGHT * SHADING_DEPTH;
			if (wolf->raycast.shading < 0)
				wolf->raycast.shading = 0;

			wolf->raycast.test_x = (int)(wolf->cam.pos_x + wolf->raycast.eye_x * wolf->raycast.distance_towall);
			wolf->raycast.test_y = (int)(wolf->cam.pos_y + wolf->raycast.eye_y * wolf->raycast.distance_towall);

			if (wolf->raycast.test_x < 0 || wolf->raycast.test_x >= wolf->mapdata.nbcol || wolf->raycast.test_y < 0 || wolf->raycast.test_y >= wolf->mapdata.nbl)
			{
				wolf->raycast.hit_wall = 1;
				wolf->raycast.distance_towall = MAX_DEPTH;
			}
			else if (wolf->mapdata.map[wolf->raycast.test_y][wolf->raycast.test_x] == WALL)
				wolf->raycast.hit_wall = 1;


		}

		//Check if there is no # a bit before the end of the ray casted
		/* double TestX_before;
		double	TestY_before;
		double before;
		int hitbefore;

		before = 0.1;
		int inc = 0;
		hitbefore = 0;
		TestX_before = wolf->raycast.test_x;
		TestY_before = wolf->raycast.test_y;
		while (hitbefore == 0 && wolf->raycast.distance_towall > 0)
		{
			TestX_before -= before;
			TestY_before -= before;

			if (wolf->mapdata.map[(int)TestY_before][(int)TestX_before] == WALL)
			{
				wolf->raycast.distance_towall *= before * inc;
				hitbefore = 1;
			}
		} */

		//--------------------------------------
		// Determine where X and Y of the wall has been collided
	
		wolf->calc.block_mid_x = (double)(wolf->raycast.test_x) + 0.5;
		wolf->calc.block_mid_y = (double)(wolf->raycast.test_y) + 0.5;
		wolf->calc.test_point_x = wolf->cam.pos_x + wolf->raycast.eye_x * wolf->raycast.distance_towall;
		wolf->calc.test_point_y = wolf->cam.pos_y + wolf->raycast.eye_y * wolf->raycast.distance_towall;
		wolf->calc.test_angle = atan2((wolf->calc.test_point_y - wolf->calc.block_mid_y), (wolf->calc.test_point_x - wolf->calc.block_mid_x));
		wolf->calc.sample_x = 0;
		if (wolf->calc.test_angle >= -PI * 0.25 && wolf->calc.test_angle <= PI * 0.25)
		{
			wolf->calc.sample_x = wolf->calc.test_point_y - (double)wolf->raycast.test_y - 1;
			wolf->orientation = WEST;
		}
		else if (wolf->calc.test_angle >= PI * 0.25 && wolf->calc.test_angle <= PI * 0.75)
		{
			wolf->calc.sample_x = wolf->calc.test_point_x - (double)wolf->raycast.test_x;
			wolf->orientation = NORTH;
		}
		else if (wolf->calc.test_angle <= -PI * 0.25 && wolf->calc.test_angle >= -PI * 0.75)
		{
			wolf->calc.sample_x = wolf->calc.test_point_x - (double)wolf->raycast.test_x - 1;
			wolf->orientation = SOUTH;
		}
		else if (wolf->calc.test_angle >= PI * 0.75 || wolf->calc.test_angle <= -PI * 0.75)
		{
			wolf->calc.sample_x = wolf->calc.test_point_y - (double)wolf->raycast.test_y;
			wolf->orientation = EAST;
		}
		wolf->calc.sample_x = fabs(wolf->calc.sample_x - (int)wolf->calc.sample_x);

		//----------------------------------------
		
		wolf->raycast.distance_towall *= cos(wolf->cam.angle - wolf->raycast.ray_angle); //fix fisheye distorsion
		int Ceiling = (double)(HEIGHT / 2) - (double)HEIGHT / wolf->raycast.distance_towall * WALL_SIZE;		
		int Floor = HEIGHT - Ceiling;

		wolf->raycast.y_render = 0;
		while (wolf->raycast.y_render < HEIGHT)
		{
			if (wolf->raycast.y_render < Ceiling) // UP
				wolf->screen_pixels[wolf->raycast.y_render * WIDTH + wolf->raycast.x_render] = DODGER_BLUE;
			else if (wolf->raycast.y_render >= Ceiling && wolf->raycast.y_render <= Floor) // WALL
			{
				wolf->calc.sample_y = ((double)wolf->raycast.y_render - (double)Ceiling) / ((double)Floor - (double)Ceiling);
				wolf->calc.sample_y = fabs(wolf->calc.sample_y - (int)wolf->calc.sample_y);

				if (wolf->orientation == NORTH)
				{
					int surfaceY = wolf->calc.sample_y * wolf->surface_wall_north->w;
					int	surfaceX = wolf->calc.sample_x * wolf->surface_wall_north->h;
					wolf->screen_pixels[wolf->raycast.y_render * WIDTH + wolf->raycast.x_render] = wolf->pixels_wall_north[surfaceY * wolf->surface_wall_north->w + surfaceX]; // brick_wall "texturing"
				}
				else if (wolf->orientation == SOUTH)
				{
					int surfaceY = wolf->calc.sample_y * wolf->surface_wall_south->w;
					int	surfaceX = wolf->calc.sample_x * wolf->surface_wall_south->h;
					wolf->screen_pixels[wolf->raycast.y_render * WIDTH + wolf->raycast.x_render] = wolf->pixels_wall_south[surfaceY * wolf->surface_wall_south->w + surfaceX]; // brick_wall "texturing"
				}
				else if (wolf->orientation == EAST)
				{
					int surfaceY = wolf->calc.sample_y * wolf->surface_wall_east->w;
					int	surfaceX = wolf->calc.sample_x * wolf->surface_wall_east->h;
					wolf->screen_pixels[wolf->raycast.y_render * WIDTH + wolf->raycast.x_render] = wolf->pixels_wall_east[surfaceY * wolf->surface_wall_east->w + surfaceX]; // brick_wall "texturing"
				}
				else if (wolf->orientation == WEST)
				{
					int surfaceY = wolf->calc.sample_y * wolf->surface_wall_west->w;
					int	surfaceX = wolf->calc.sample_x * wolf->surface_wall_west->h;
					wolf->screen_pixels[wolf->raycast.y_render * WIDTH + wolf->raycast.x_render] = wolf->pixels_wall_west[surfaceY * wolf->surface_wall_west->w + surfaceX]; // brick_wall "texturing"
				}
				//CARDINAL COLORING
				/* if (wolf->orientation == NORTH)
					wolf->pixels[wolf->raycast.y_render * WIDTH + wolf->raycast.x_render] = RED; // cardinal coloring
				else if (wolf->orientation == SOUTH)
					wolf->pixels[wolf->raycast.y_render * WIDTH + wolf->raycast.x_render] = BLUE; // cardinal coloring
				else if (wolf->orientation == EAST)
					wolf->pixels[wolf->raycast.y_render * WIDTH + wolf->raycast.x_render] = YELLOW; // cardinal coloring
				else if (wolf->orientation == WEST)
					wolf->pixels[wolf->raycast.y_render * WIDTH + wolf->raycast.x_render] = PURPLE; // cardinal coloring */


				//wolf->pixels[wolf->raycast.y_render * WIDTH + wolf->raycast.x_render] = RGBA_to_uint32(255 * wolf->raycast.shading, 255 * wolf->raycast.shading, 255 * wolf->raycast.shading, 0); //non textured wall
			}
			else  //DOWN
				wolf->screen_pixels[wolf->raycast.y_render * WIDTH + wolf->raycast.x_render] = rgba_to_uint32(0, 255 * ((wolf->raycast.y_render - HEIGHT * 0.5) / HEIGHT), 0, 0);
			wolf->raycast.y_render++;
		}
		wolf->raycast.x_render++;
	}
	
	//---------------------------------------------------------------------------------------------------------
	//###### printing 2D map view from above + red dot for camera location ######
	int		i;
	int		j;
	int		x;
	int		y;
	int		def_x;
	int		def_y;
	SDL_bool done;
	
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
					wolf->screen_pixels[y * WIDTH + x] = LIME;
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
					wolf->screen_pixels[y * WIDTH + x] = GRAY;
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
	
	// TESTING IMAGE COPY PIXEL BY PIXEL ON SCREEN
	/* wolf->raycast.y_render = 10;
	int	imgX = 0;
	int imgY = 0;
	while (wolf->raycast.y_render < HEIGHT)
	{
		wolf->raycast.x_render = 10;
		imgX = 0;
		while (wolf->raycast.x_render < WIDTH)
		{
			if (imgX < 636 && imgY < 639)
				wolf->pixels[wolf->raycast.y_render * WIDTH + wolf->raycast.x_render] = pixels_wall[imgY * 636 + imgX];
			imgX++;
			wolf->raycast.x_render++;
		}
		imgY++;
		wolf->raycast.y_render++;
	} */

	
	//---------------------------------------------------------------------------------------------------------

	// ###### DISPLAYING ######
	SDL_UnlockTexture(wolf->texture);
	SDL_RenderCopy(wolf->renderer, wolf->texture, NULL, NULL);

	// TESTING IMAGE COPY ON SCREEN
	//SDL_Rect test1 = {0, 0, 636, 639};
	//SDL_Rect test2 = {WIDTH * 0.25, HEIGHT * 0.25, 500, 400};
	//SDL_RenderCopy(wolf->renderer, wolf->surface_wall.texture, &test1, &test2);
	
	SDL_SetRenderDrawColor(wolf->renderer, 255, 0, 0, 255);
	SDL_RenderDrawLine(wolf->renderer, wolf->cam.pos_x * BLOCK, wolf->cam.pos_y * BLOCK,
						(wolf->cam.pos_x + sin(wolf->cam.angle)) * BLOCK, (wolf->cam.pos_y + cos(wolf->cam.angle)) * BLOCK); //RAY from cam
	SDL_SetRenderDrawColor(wolf->renderer, 255, 255, 255, 255);
	SDL_RenderDrawPoint(wolf->renderer, wolf->cam.pos_x * BLOCK, wolf->cam.pos_y * BLOCK);

	SDL_RenderPresent(wolf->renderer);
}