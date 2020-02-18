/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcanteau <jcanteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 16:04:06 by jcanteau          #+#    #+#             */
/*   Updated: 2020/02/18 17:22:00 by jcanteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

uint32_t	RGBA_to_uint32(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
	return ((r << 24) + (g << 16) + (b << 8) + a);
}

void	ft_print(t_env *wolf)
{
	
	int	i;
	int	j;

	//void	*tmp;
	int		pitch;
	SDL_bool done;

	int		x;
	int		y;
	int		def_x;
	int		def_y;
	
	SDL_LockTexture(wolf->texture, NULL, (void **)&(wolf->pixels), &pitch);
	//wolf->pixels = tmp;
	
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
		double		shading = 1;

		EyeX = sin(RayAngle);
		EyeY = cos(RayAngle);

		while (hitWall == 0 && distanceToWall < MAX_DEPTH)
		{
			distanceToWall += PRECISION;
			shading -= PRECISION * SHADING_DEPTH;
			if (shading < 0)
				shading = 0;

			TestX = (int)(wolf->cam.pos_x + EyeX * distanceToWall);
			TestY = (int)(wolf->cam.pos_y + EyeY * distanceToWall);

			if (TestX < 0 || TestX >= wolf->mapdata.nbcol || TestY < 0 || TestY >= wolf->mapdata.nbl)
			{
				hitWall = 1;
				distanceToWall = MAX_DEPTH;
			}
			else
			{
				if (wolf->mapdata.map[TestY][TestX] == WALL)
					hitWall = 1; 
			}
		}

		int Ceiling = (double)(HEIGHT / 2) - (double)HEIGHT / distanceToWall;
		int Floor = HEIGHT - Ceiling;

		//printf("for xRender = %d\tCeiling = %d\tFloor = %d\n", xRender, Ceiling, Floor);
		yRender = 0;
		while (yRender < HEIGHT)
		{
			if (yRender < Ceiling) // UP
				wolf->pixels[yRender * WIDTH + xRender] = DODGER_BLUE;
			else if (yRender >= Ceiling && yRender <= Floor) // WALL
				wolf->pixels[yRender * WIDTH + xRender] = RGBA_to_uint32(255 * shading, 255 * shading, 255 * shading, 0);
			else  //DOWN
				wolf->pixels[yRender * WIDTH + xRender] = RGBA_to_uint32(0, 255 * ((yRender - HEIGHT * 0.5)/ HEIGHT), 0, 0);
			yRender++;
		}
		xRender++;
	}

	//---------------------------------------------------------------------------------------------------------
	//###### printing 2D map view from above + red dot for camera location ######
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
	
	//SDL_RenderDrawLine(wolf->renderer, wolf->cam.pos_x, wolf->cam.pos_y, wolf->cam.pos_x + wolf->cam.dir_x * 10, wolf->cam.pos_y + wolf->cam.dir_y * 10);
	

	//---------------------------------------------------------------------------------------------------------

	// ###### DISPLAYING ######
	SDL_UnlockTexture(wolf->texture);
	SDL_RenderCopy(wolf->renderer, wolf->texture, NULL, NULL);

	
	SDL_SetRenderDrawColor(wolf->renderer, 255, 0, 0, 255);
	SDL_RenderDrawLine(wolf->renderer, wolf->cam.pos_x * BLOCK, wolf->cam.pos_y * BLOCK,
						(wolf->cam.pos_x + sin(wolf->cam.angle)) * BLOCK, (wolf->cam.pos_y + cos(wolf->cam.angle)) * BLOCK); //RAY from cam
	SDL_SetRenderDrawColor(wolf->renderer, 0, 0, 255, 255);
	SDL_RenderDrawPoint(wolf->renderer, wolf->cam.pos_x * BLOCK, wolf->cam.pos_y * BLOCK);

	SDL_RenderPresent(wolf->renderer);
}