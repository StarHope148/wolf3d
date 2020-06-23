/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcanteau <jcanteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 21:29:29 by jcanteau          #+#    #+#             */
/*   Updated: 2020/06/23 21:41:59 by jcanteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void    ft_set_points(t_env *wolf)
{
    wolf->minimap.done = 0;
	wolf->minimap.x = wolf->minimap.j * BLOCK;
	wolf->minimap.y = wolf->minimap.i * BLOCK;
	wolf->minimap.def_x = wolf->minimap.x;
	wolf->minimap.def_y = wolf->minimap.y;
}

void    ft_draw_minimap_wall(t_env *wolf)
{
    while (wolf->minimap.done == 0)
    {
        wolf->screen_pixels[wolf->minimap.y * WIDTH + wolf->minimap.x] = LIME;
        wolf->minimap.x++;
        if (wolf->minimap.x > wolf->minimap.def_x + BLOCK)
        {
            wolf->minimap.x = wolf->minimap.j * BLOCK;
            wolf->minimap.y++;
        }
        if (wolf->minimap.y > wolf->minimap.def_y + BLOCK)
            wolf->minimap.done = 1;
    }
}

void    ft_draw_minimap_empty_space(t_env *wolf)
{
    while (wolf->minimap.done == 0)
    {
        wolf->screen_pixels[wolf->minimap.y * WIDTH + wolf->minimap.x] = GRAY;
        wolf->minimap.x++;
        if (wolf->minimap.x > wolf->minimap.def_x + BLOCK)
        {
            wolf->minimap.x = wolf->minimap.j * BLOCK;
            wolf->minimap.y++;
        }
        if (wolf->minimap.y > wolf->minimap.def_y + BLOCK)
            wolf->minimap.done = 1;
    }
}

void    ft_set_SDL_minimap_colors(t_env *wolf)
{
    SDL_SetRenderDrawColor(wolf->renderer, 255, 0, 0, 255);
	SDL_RenderDrawLine(wolf->renderer, wolf->cam.pos_x * BLOCK,
                        wolf->cam.pos_y * BLOCK,
						(wolf->cam.pos_x + sin(wolf->cam.angle)) * BLOCK,
                        (wolf->cam.pos_y + cos(wolf->cam.angle)) * BLOCK);
	SDL_SetRenderDrawColor(wolf->renderer, 255, 255, 255, 255);
	SDL_RenderDrawPoint(wolf->renderer, wolf->cam.pos_x * BLOCK,
                        wolf->cam.pos_y * BLOCK);
}

void    ft_draw_minimap(t_env *wolf)
{
    wolf->minimap.i = 0;
	while (wolf->minimap.i < (int)wolf->mapdata.nbl)
	{
		wolf->minimap.j = 0;
		while (wolf->minimap.j < (int)wolf->mapdata.nbcol)
		{
            ft_set_points(wolf);
			if (wolf->mapdata.map[wolf->minimap.i][wolf->minimap.j] == WALL)
                ft_draw_minimap_wall(wolf);
			else if (wolf->mapdata.map[wolf->minimap.i]
                    	[wolf->minimap.j] == EMPTY)
                ft_draw_minimap_empty_space(wolf);
			wolf->minimap.j++;
		}
		wolf->minimap.i++;
	}
}