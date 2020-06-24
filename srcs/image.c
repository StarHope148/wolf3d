/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcanteau <jcanteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 16:04:06 by jcanteau          #+#    #+#             */
/*   Updated: 2020/06/24 15:58:26 by jcanteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_update_screen(t_env *wolf)
{
	SDL_RenderCopy(wolf->renderer, wolf->texture, NULL, NULL);
	ft_set_sdl_minimap_colors(wolf);
	SDL_RenderPresent(wolf->renderer);
}

void	ft_pixel_access_bmp_images(t_env *wolf)
{
	wolf->pixels_wall_north = wolf->surface_wall_north->pixels;
	wolf->pixels_wall_south = wolf->surface_wall_south->pixels;
	wolf->pixels_wall_west = wolf->surface_wall_west->pixels;
	wolf->pixels_wall_east = wolf->surface_wall_east->pixels;
}

void	ft_print(t_env *wolf)
{
	SDL_LockTexture(wolf->texture, NULL, (void *)&(wolf->screen_pixels),
					&(wolf->pitch));
	ft_pixel_access_bmp_images(wolf);
	ft_raycaster(wolf);
	ft_draw_minimap(wolf);
	SDL_UnlockTexture(wolf->texture);
	ft_update_screen(wolf);
}
