/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcanteau <jcanteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 16:04:06 by jcanteau          #+#    #+#             */
/*   Updated: 2020/06/22 20:28:22 by jcanteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

uint32_t	RGBA_to_uint32(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
	return ((r << 24) + (g << 16) + (b << 8) + a);
}

void	ft_print(t_env *wolf)
{
	int		pitch;
	
	SDL_LockTexture(wolf->texture, NULL, (void *)&(wolf->screen_pixels), &pitch);
	SDL_LockSurface(wolf->surface_wall_north);
	SDL_LockSurface(wolf->surface_wall_south);
	SDL_LockSurface(wolf->surface_wall_east);
	SDL_LockSurface(wolf->surface_wall_west);
	Uint32 *pixels_wall_north = wolf->surface_wall_north->pixels;
	Uint32 *pixels_wall_south = wolf->surface_wall_south->pixels;
	Uint32 *pixels_wall_west = wolf->surface_wall_west->pixels;
	Uint32 *pixels_wall_east = wolf->surface_wall_east->pixels;

	
	//---------------------------------------------------------------------------------------------------------

	// ###### RAYTRACER ###### 

	int		xRender;
	int		yRender;
	double 	EyeX;
	double 	EyeY;
	int		TestX;
	int		TestY;

	xRender = 0;
	while (xRender < WIDTH)
	{
		double	RayAngle = (wolf->cam.angle + wolf->cam.fov / 2.0) - ((double)xRender / (double)WIDTH) * wolf->cam.fov;
		double	distanceToWall = 0;
		int		hitWall = 0;
		double	shading = 1;

		EyeX = sin(RayAngle);
		EyeY = cos(RayAngle);

		while (hitWall == 0 && distanceToWall < MAX_DEPTH)
		{
			distanceToWall += wolf->precision;
			shading -= RAY_LENGHT * SHADING_DEPTH;
			if (shading < 0)
				shading = 0;

			TestX = (int)(wolf->cam.pos_x + EyeX * distanceToWall);
			TestY = (int)(wolf->cam.pos_y + EyeY * distanceToWall);

			if (TestX < 0 || TestX >= wolf->mapdata.nbcol || TestY < 0 || TestY >= wolf->mapdata.nbl)
			{
				hitWall = 1;
				distanceToWall = MAX_DEPTH;
			}
			else if (wolf->mapdata.map[TestY][TestX] == WALL)
				hitWall = 1;


		}

		//Check if there is no # a bit before the end of the ray casted
		/* double TestX_before;
		double	TestY_before;
		double before;
		int hitbefore;

		before = 0.1;
		int inc = 0;
		hitbefore = 0;
		TestX_before = TestX;
		TestY_before = TestY;
		while (hitbefore == 0 && distanceToWall > 0)
		{
			TestX_before -= before;
			TestY_before -= before;

			if (wolf->mapdata.map[(int)TestY_before][(int)TestX_before] == WALL)
			{
				distanceToWall *= before * inc;
				hitbefore = 1;
			}
		} */

		//--------------------------------------
		// Determine where X and Y of the wall has been collided
	
		double sampleX;
		double sampleY;

		double BlockMidX = (double)(TestX) + 0.5;
		double BlockMidY = (double)(TestY) + 0.5;

		double TestPointX = wolf->cam.pos_x + EyeX * distanceToWall;
		double TestPointY = wolf->cam.pos_y + EyeY * distanceToWall;

		
		double testAngle = atan2((TestPointY - BlockMidY), (TestPointX - BlockMidX));

		sampleX = 0;
		if (testAngle >= -PI * 0.25 && testAngle <= PI * 0.25)		//WEST
		{
			sampleX = TestPointY - (double)TestY - 1;
			wolf->orientation = WEST;
		}
		else if (testAngle >= PI * 0.25 && testAngle <= PI * 0.75)		//NORTH
		{
			sampleX = TestPointX - (double)TestX;
			wolf->orientation = NORTH;
		}
		else if (testAngle <= -PI * 0.25 && testAngle >= -PI * 0.75)	//SOUTH
		{
			sampleX = TestPointX - (double)TestX - 1;
			wolf->orientation = SOUTH;
		}
		else if (testAngle >= PI * 0.75 || testAngle <= -PI * 0.75)		//EAST
		{
			sampleX = TestPointY - (double)TestY;
			wolf->orientation = EAST;
		}

		sampleX = fabs(sampleX - (int)sampleX);
		//----------------------------------------
		//printf("distanceToWall = %f\n", distanceToWall);			//DEBUG
		distanceToWall *= cos(wolf->cam.angle - RayAngle); //fix fisheye distorsion
		int Ceiling = (double)(HEIGHT / 2) - (double)HEIGHT / distanceToWall * WALL_SIZE;		
		int Floor = HEIGHT - Ceiling;


		yRender = 0;
		while (yRender < HEIGHT)
		{
			if (yRender < Ceiling) // UP
				wolf->screen_pixels[yRender * WIDTH + xRender] = DODGER_BLUE;
			else if (yRender >= Ceiling && yRender <= Floor) // WALL
			{
				sampleY = ((double)yRender - (double)Ceiling) / ((double)Floor - (double)Ceiling);
				sampleY = fabs(sampleY - (int)sampleY);

				if (wolf->orientation == NORTH)
				{
					int surfaceY = sampleY * wolf->surface_wall_north->w;
					int	surfaceX = sampleX * wolf->surface_wall_north->h;
					wolf->screen_pixels[yRender * WIDTH + xRender] = pixels_wall_north[surfaceY * wolf->surface_wall_north->w + surfaceX]; // brick_wall "texturing"
				}
				else if (wolf->orientation == SOUTH)
				{
					int surfaceY = sampleY * wolf->surface_wall_south->w;
					int	surfaceX = sampleX * wolf->surface_wall_south->h;
					wolf->screen_pixels[yRender * WIDTH + xRender] = pixels_wall_south[surfaceY * wolf->surface_wall_south->w + surfaceX]; // brick_wall "texturing"
				}
				else if (wolf->orientation == EAST)
				{
					int surfaceY = sampleY * wolf->surface_wall_east->w;
					int	surfaceX = sampleX * wolf->surface_wall_east->h;
					wolf->screen_pixels[yRender * WIDTH + xRender] = pixels_wall_east[surfaceY * wolf->surface_wall_east->w + surfaceX]; // brick_wall "texturing"
				}
				else if (wolf->orientation == WEST)
				{
					int surfaceY = sampleY * wolf->surface_wall_west->w;
					int	surfaceX = sampleX * wolf->surface_wall_west->h;
					wolf->screen_pixels[yRender * WIDTH + xRender] = pixels_wall_west[surfaceY * wolf->surface_wall_west->w + surfaceX]; // brick_wall "texturing"
				}
				//CARDINAL COLORING
				/* if (wolf->orientation == NORTH)
					wolf->pixels[yRender * WIDTH + xRender] = RED; // cardinal coloring
				else if (wolf->orientation == SOUTH)
					wolf->pixels[yRender * WIDTH + xRender] = BLUE; // cardinal coloring
				else if (wolf->orientation == EAST)
					wolf->pixels[yRender * WIDTH + xRender] = YELLOW; // cardinal coloring
				else if (wolf->orientation == WEST)
					wolf->pixels[yRender * WIDTH + xRender] = PURPLE; // cardinal coloring */


				//wolf->pixels[yRender * WIDTH + xRender] = RGBA_to_uint32(255 * shading, 255 * shading, 255 * shading, 0); //non textured wall
			}
			else  //DOWN
				wolf->screen_pixels[yRender * WIDTH + xRender] = RGBA_to_uint32(0, 255 * ((yRender - HEIGHT * 0.5) / HEIGHT), 0, 0);
			yRender++;
		}
		xRender++;
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
	/* yRender = 10;
	int	imgX = 0;
	int imgY = 0;
	while (yRender < HEIGHT)
	{
		xRender = 10;
		imgX = 0;
		while (xRender < WIDTH)
		{
			if (imgX < 636 && imgY < 639)
				wolf->pixels[yRender * WIDTH + xRender] = pixels_wall[imgY * 636 + imgX];
			imgX++;
			xRender++;
		}
		imgY++;
		yRender++;
	} */

	
	//---------------------------------------------------------------------------------------------------------

	//display wall_brick texture for testing
	//for (int texture_y = 0; texture_y < wolf->wall_brick_img.height; texture_y++)
	//	for (int texture_x = 0; texture_x < wolf->wall_brick_img.width; texture_x++)
	//		wolf->pixels[texture_y * WIDTH + texture_x] = wolf->wall_brick_img.pixels[texture_y * wolf->wall_brick_img.width + texture_x];
		
	

	// ###### DISPLAYING ######
	SDL_UnlockTexture(wolf->texture);
	SDL_UnlockSurface(wolf->surface_wall_north);
	SDL_UnlockSurface(wolf->surface_wall_south);
	SDL_UnlockSurface(wolf->surface_wall_east);
	SDL_UnlockSurface(wolf->surface_wall_west);

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