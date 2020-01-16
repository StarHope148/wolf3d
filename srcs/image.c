/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcanteau <jcanteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 16:04:06 by jcanteau          #+#    #+#             */
/*   Updated: 2020/01/16 16:57:07 by jcanteau         ###   ########.fr       */
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
			if (wolf->mapdata.map[i][j] == '1')
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
			else if (wolf->mapdata.map[i][j] == '0')
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
	

	//---------------------------------------------------------------------------------------------------------

	// ###### DISPLAYING ######
	SDL_UnlockTexture(wolf->texture);
	SDL_RenderCopy(wolf->renderer, wolf->texture, NULL, NULL);

	SDL_RenderDrawPoint(wolf->renderer, wolf->cam.x, wolf->cam.y);
	SDL_SetRenderDrawColor(wolf->renderer, 255, 0, 0, 255);
	
	SDL_RenderDrawLine(wolf->renderer, wolf->cam.x, wolf->cam.y , BLOCK, BLOCK); //RAY from cam

	SDL_RenderPresent(wolf->renderer);
}